#ifndef SELENA_ARENA_ALLOC
#define SELENA_ARENA_ALLOC

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# define NOMINMAX
# include <process.h>
# include <Windows.h>
// For VirtualAlloc2 and VirtualFreeEx
# pragma comment(lib, "mincore")
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
# include <sys/mman.h>
# include <unistd.h>
#endif // ^^^ _WIN32 ^^^

#include <atomic>
#include <bit>
#include <bitset>
#include <new>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#define SELENA_ARENA_OVERLOAD_NEW_DELETE
#define SELENA_ARENA_CLEANUP_ON_EXIT

namespace selena {

class arena_alloc {
public:
  static void* alloc(
    const std::size_t size_,
    const std::align_val_t alignment_ = static_cast<std::align_val_t>(alignof(std::max_align_t))
  ) noexcept {
    if (!size_) {
      return nullptr;
    }

    tl_teardown_.ping();

    const std::size_t align_val_{ static_cast<std::size_t>(alignment_) };

    // Required size
    const std::size_t req_size_{ size_ + align_val_ + sizeof(allocator_header) };

    // If required size is less than or equal to a page size, allocate it inside a page,
    // or create a new page.
    if (req_size_ <= page_size) {
      const std::size_t class_idx_{ get_class_idx(req_size_) };

      if (tl_free_lists_[class_idx_]) {
        free_node* node_{ tl_free_lists_[class_idx_] };
        tl_free_lists_[class_idx_] = node_->next_;

        /*
         * -------------------------------------------------------------------...
         * |                          |                      |
         * |    Alignment Padding     |   allocation header  |  actual data
         * | 0 to align_val - 1 bytes |                      |
         * |                          |                      |
         * -------------------------------------------------------------------...
         * ^                          ^                      ^
         * |                          |                      |
         * base pointer      header starts here       data starts here
         *
         * creating ascii art is :catDespair:
         */

         // Start of memory.
        std::byte* base_ptr_{ reinterpret_cast<std::byte*>(node_) };

        // Move past the header and align it to the next multiple of alignment.
        std::byte* data_ptr_{
          reinterpret_cast<std::byte*>((reinterpret_cast<std::uintptr_t>(base_ptr_) + sizeof(allocator_header) + align_val_ - 1) & ~(align_val_ - 1))
        };

        // Move back up and store header.
        allocator_header* header_{ reinterpret_cast<allocator_header*>(data_ptr_ - sizeof(allocator_header)) };
        header_->size_ = get_chunk_size(class_idx_);
        header_->padding_offs_ = static_cast<std::size_t>(data_ptr_ - base_ptr_);

        return data_ptr_;
      }

      // Triggered if free lists didn't have a page.

      void* page_ptr_{ alloc_pages(1) };

      if (!page_ptr_) {
        return nullptr;
      }

      const std::size_t chunk_sz_{ get_chunk_size(class_idx_) };
      const std::size_t num_chunks_{ page_size / chunk_sz_ };

      // The base pointer of the newly allocated page.
      std::byte* byte_ptr_{ static_cast<std::byte*>(page_ptr_) };

      for (std::size_t i_{}; i_ < num_chunks_; ++i_) {
        // Add the address of the base pointer to the offset of current chunk. Then, convert it
        // into a node pointer.
        free_node* node_{ reinterpret_cast<free_node*>(byte_ptr_ + (i_ * chunk_sz_)) };

        // A push front operation of a LIFO stack.
        node_->next_ = tl_free_lists_[class_idx_];
        tl_free_lists_[class_idx_] = node_;
      }

      free_node* node_{ tl_free_lists_[class_idx_] };
      tl_free_lists_[class_idx_] = node_->next_;

      std::byte* base_ptr_{ reinterpret_cast<std::byte*>(node_) };
      std::byte* data_ptr_{
        reinterpret_cast<std::byte*>((reinterpret_cast<std::uintptr_t>(base_ptr_) + sizeof(allocator_header) + align_val_ - 1) & ~(align_val_ - 1))
      };

      allocator_header* header_{ reinterpret_cast<allocator_header*>(data_ptr_ - sizeof(allocator_header)) };
      header_->size_ = chunk_sz_;
      header_->padding_offs_ = static_cast<std::size_t>(data_ptr_ - base_ptr_);

      return data_ptr_;
    }

    // If required size is larger than 2 MB, allocate directly from OS.
    if (req_size_ > (arena_size - page_size)) {
      // Actual required size: size asked by user + allocation header + large allocs header.
      const std::size_t new_req_size_{ req_size_ + sizeof(large_allocs) };
      void* os_ptr_{ reserve_os(new_req_size_) };

      if (!os_ptr_) {
        return nullptr;
      }

      if (!commit_os(os_ptr_, new_req_size_)) {
        if (!release_os(os_ptr_, new_req_size_)) {
          // Memory leak!
        }

        return nullptr;
      }

      large_allocs* node_{ new(os_ptr_) large_allocs() };
      node_->size_ = new_req_size_;
      node_->npx_ = xor_ptrs<large_allocs>(nullptr, large_allocs_head_);

      if (large_allocs_head_) {
        large_allocs_head_->npx_ = xor_ptrs<large_allocs>(node_, xor_ptrs<large_allocs>(nullptr, large_allocs_head_->npx_));
      }

      large_allocs_head_ = node_;

      std::byte* base_ptr_{ static_cast<std::byte*>(os_ptr_) + sizeof(large_allocs) };
      std::byte* data_ptr_{
        reinterpret_cast<std::byte*>((reinterpret_cast<std::uintptr_t>(base_ptr_) + sizeof(allocator_header) + align_val_ - 1) & ~(align_val_ - 1))
      };

      allocator_header* header_{ reinterpret_cast<allocator_header*>(data_ptr_ - sizeof(allocator_header)) };
      header_->size_ = req_size_;
      header_->padding_offs_ = static_cast<std::size_t>(data_ptr_ - base_ptr_);

      return data_ptr_;
    }

    // Ceiling division. Adding page size, we guarantee any fractional divison would go to the
    // nearest integer towards infinity (ceiling).
    const std::size_t pages_req_{ (req_size_ + page_size - 1) >> std::countr_zero(page_size) };
    void* multi_page_ptr_{ alloc_pages(pages_req_) };

    if (!multi_page_ptr_) {
      return nullptr;
    }

    std::byte* base_ptr_{ static_cast<std::byte*>(multi_page_ptr_) };
    std::byte* data_ptr_{
      reinterpret_cast<std::byte*>((reinterpret_cast<std::uintptr_t>(base_ptr_) + sizeof(allocator_header) + align_val_ - 1) & ~(align_val_ - 1))
    };

    allocator_header* header_{ reinterpret_cast<allocator_header*>(data_ptr_ - sizeof(allocator_header)) };
    header_->size_ = pages_req_ << std::countr_zero(page_size);
    header_->padding_offs_ = static_cast<std::size_t>(data_ptr_ - base_ptr_);

    return data_ptr_;
  }

  static void free(void* ptr_) noexcept {
    if (!ptr_) {
      return;
    }

    std::byte* data_ptr_{ reinterpret_cast<std::byte*>(ptr_) };
    allocator_header* header_{ reinterpret_cast<allocator_header*>(data_ptr_ - sizeof(allocator_header)) };
    std::byte* base_ptr_{ data_ptr_ - header_->padding_offs_ };

    if (header_->size_ <= page_size) {
      const std::size_t class_idx_{ get_class_idx(header_->size_) };

      free_node* node_{ reinterpret_cast<free_node*>(base_ptr_) };
      node_->next_ = tl_free_lists_[class_idx_];
      tl_free_lists_[class_idx_] = node_;

      return;
    }

    if (header_->size_ > (arena_size - page_size)) {
      std::byte* os_ptr_{ base_ptr_ - sizeof(large_allocs) };
      large_allocs* node_{ reinterpret_cast<large_allocs*>(os_ptr_) };

      large_allocs* curr_{ large_allocs_head_ }, * prev_{ nullptr };

      while (curr_) {
        large_allocs* next_{ xor_ptrs(prev_, curr_->npx_) };

        if (curr_ == node_) {
          if (prev_) {
            prev_->npx_ = xor_ptrs<large_allocs>(xor_ptrs<large_allocs>(prev_->npx_, curr_), next_);
          } else {
            large_allocs_head_ = next_;
          }

          if (next_) {
            next_->npx_ = xor_ptrs<large_allocs>(prev_, xor_ptrs<large_allocs>(curr_, next_->npx_));
          }

          break;
        }

        prev_ = curr_;
        curr_ = next_;
      }

      if (release_os(os_ptr_, node_->size_)) {
        // Update counter in actual code
      } else {
        // Memory leak!
      }
      return;
    }

    free_pages(base_ptr_, header_->size_ >> std::countr_zero(page_size));
  }

  static inline const std::size_t page_size{
#ifdef _WIN32
    static_cast<std::size_t>([]() -> SYSTEM_INFO {
      SYSTEM_INFO temp_;
      std::memset(&temp_, 0, sizeof(temp_));
      GetSystemInfo(&temp_);
      return temp_;
    }().dwPageSize)
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
    static_cast<std::size_t>(sysconf(_SC_PAGESIZE))
#endif // ^^^ _WIN32 ^^^
  };

  static constexpr inline std::size_t arena_size{ 1u << 21 };

private:
  struct alignas(std::max_align_t) allocator_header {
    std::size_t size_;
    std::size_t padding_offs_;
  };

  struct free_node {
    free_node* next_;
  };

  struct arena {
    arena* npx_; // Thread-local traversal
    std::uint64_t committed_pages_[8]; // 512 bits segmented into 8 64-bit blocks
  };

  struct large_allocs {
    large_allocs* npx_; // Thread-local traversal
    std::size_t size_;
  };

  struct thread_teardown {
    inline void ping() const noexcept {}

    ~thread_teardown() noexcept {
      arena* curr_{ arena_head_ }, * prev_{ nullptr };

      while (curr_) {
        arena* next_{ xor_ptrs(prev_, curr_->npx_) };

        std::size_t committed_bytes_{};

        for (std::size_t i_{}; i_ < 8; ++i_) {
          const std::uint64_t block_{ curr_->committed_pages_[i_] };
          committed_bytes_ += static_cast<std::size_t>(std::popcount(block_)) << std::countr_zero(page_size);
        }

        if (!release_os(curr_, arena_size)) {
          // Memory leak!
        }

        prev_ = curr_; curr_ = next_;
      }

      arena_head_ = nullptr;

      large_allocs* curr_large_{ large_allocs_head_ };
      large_allocs* prev_large_{ nullptr };

      while (curr_large_) {
        large_allocs* next_large_{ xor_ptrs<large_allocs>(prev_large_, curr_large_->npx_) };

        if (!release_os(curr_large_, curr_large_->size_)) {
          // Memory leak!
        }

        prev_large_ = curr_large_;
        curr_large_ = next_large_;
      }

      large_allocs_head_ = nullptr;

      std::memset(&tl_free_lists_, 0, sizeof(tl_free_lists_));
    }
  };

  static thread_local inline arena* arena_head_{ nullptr };
  static thread_local inline large_allocs* large_allocs_head_{ nullptr };
  static thread_local inline thread_teardown tl_teardown_{};

  static constexpr inline std::size_t num_free_lists_{ 56 };
  static thread_local inline free_node* tl_free_lists_[num_free_lists_]{};

  template <typename T_>
  static inline T_* xor_ptrs(const T_* const next_, const T_* const prev_) noexcept {
    return reinterpret_cast<T_*>(
      reinterpret_cast<std::uint64_t>(next_) ^ reinterpret_cast<std::uint64_t>(prev_)
      );
  }

  // Maps an exact requested size to a bucket index (0 to 55)
  static inline const std::size_t get_class_idx(const std::size_t size_) noexcept {
    if (size_ <= 256) {
      // This part here creates 32 buckets spaced by 8 bytes, 32 * 8 = 256.
      // Sizes 1-8 goes to index 0, sizes 9-16 to index 1... sizes 249-256 to index 31.
      return (size_ - 1) >> 3; // basically, size_ / 8
    }

    // For sizes larger than 256 bytes, creating 8 byte-spaced chunks will
    // require thousands of chunks. So, switch to logarithmic scale and
    // divide into subranges, 256-512, 512-1024, etc.

    // Sub 1 to handle cases when size is power of 2.
    const std::size_t s_{ size_ - 1 };

    // Calc. MSB. This gives which power-of-2 range this size belongs to.
    const std::size_t b_{ static_cast<std::size_t>(std::bit_width(s_)) - 1 };

    // Mathematically, b_ gives exponent, the n in 2^n. We are to divide a range (ex. 256-512)
    // into 4 subgroups. In case of exponents, division = subtraction. For example, consider 256.
    // We know 256 = 2^8. 8-2 comes to be 6. 2^6 = 64. On the other hand, 256/4 = 64.
    // This is basically that, division by 4 = subtraction of exponents by 2.
    const std::size_t shift_{ b_ - 2 };

    // Calculates starting index of this group. Subtract 8 from b_ as the minimum b_ can be is 8.
    // log2(256) = 8. Left shift by 2 = multiply by 4. 4 bcs there are 4 subgroups inside a group.
    const std::size_t base_idx_{ 32 + ((b_ - 8) << 2) };

    // Extract the next two bits of the size to determine which of the four subgroups (0, 1, 2 or 3)
    // this size falls into. Since the target sub bracket must always be a value between 0 and 3,
    // AND with 3.
    const std::size_t sub_idx_{ (s_ >> shift_) & 3 };

    /*
     * Let size = 300.
     * s_ = size - 1 = 299.
     * b_ = std::bit_width(s_) - 1 = std::bit_width(299) - 1 = 9 - 1 = 8.
     * shift_ = b_ - 2 = 6. Look at how 300/4 = 75 has the (floor) power of 2, 64.
     * base_idx_ = 32 + ((b_ - 8) << 2) = 32 + ((8 - 8) << 2) = 32 + 0 = 32.
     * sub_idx_ = (s_ >> shift_) & 3 = (299 >> 6) & 3 = 4 & 3 = 0
     * In case of 300, returned value will be base_idx_ + sub_idx_ = 32 + 0 = 32.
     */

    return base_idx_ + sub_idx_;
  }

  // Maps a bucket index back to its aligned chunk size
  static inline const std::size_t get_chunk_size(const std::size_t idx_) noexcept {
    // This entire function basically reverses the math of get_class_idx and findds the
    // nearest chunk size.

    if (idx_ < 32) {
      // Adds 1 and multiplies by 8.
      // Index 0 will return 8, index 1 will return 16... index 31 will return 256.
      return (idx_ + 1) << 3;
    }

    // Recalc. the base power-of-2 group by subtracting 32 (as the first 32 buckets are alrd
    // over with), multiplying by 4 and adding 8.
    const std::size_t b_{ ((idx_ - 32) >> 2) + 8 };

    // Extract subbucket index (0-3).
    const std::size_t sub_{ (idx_ - 32) & 3 };

    // Calc. shift. Reasoning is same as was in get_class_idx for shift_.
    const std::size_t shift_{ b_ - 2 };

    // Base size of the lower bound of this group (ex, 256, 512), will always be a power of 2.
    const std::size_t base_{ std::size_t(1) << b_ };

    // Calculates the uniform size step for the 4 subgroups inside this group.
    const std::size_t step_{ std::size_t(1) << shift_ };

    /*
     * Example, consider the group 256-512. We have 512-256 = 256. Dividing this into 4 subgroups, we get,
     * 320, 384, 448, 512. Each one increases by 64. Why? Because 256 / 4 = 64!.
     * Second, consider the result 32 obtained from the example in get_class_idx.
     * b_ = ((idx_ - 32) >> 2 + 8 = (32 - 32) >> 2 + 8 = 8.
     * In get_class_idx, we also had b_ = 8!
     * sub_ = (idx_ - 32) & 3 = (32 - 32) & 3 = 0.
     * shift_ = b_ - 2 = 8 - 2 = 6. In get_class_idx, we also had shift_ = 6!
     * base_ = 1 << b_ = 2^b_ = 2^8 = 256, aka this falls in group 256-512.
     * step_ = 1 << shift_ = 2^shift_ = 2^6 = 64, aka the step is acurately 64 for this group!
     */

    return base_ + ((sub_ + 1) * step_);
  }

  /*
   * This arena_alloc works on three different ways:
   * a. If required size (in alloc) is less than 2 MB, it allocates inside an arena.
   * b. If required size (in alloc) is equal to 2 MB, the alloc function internally
   *   calculates its req_size_ as 2 MB + 16 bytes (from alignment) + 16 bytes (from sizeof(allocation_header),
   *   which equals to 2,097,184. Assuming page size comes out to be 4 KB, the test "req_size_ > (arena_size - page_size)"
   *   evaluates to true, as 2,097,184 is greater than 2,093,056. This does a direct OS allocation, aka the not-in-if block
   *   part of this function.
   * c. When an arena needs to be allocated, this function passes the alignment requirement on Windows, and allocates 4 MB
   *   on Linux. On Windows, this is handled natively. On Linux, this function truncates to match a 2 MB alignment.
   *
   * @return A pointer to the base address of allocated memory.
   */
  static inline void* reserve_os(const std::size_t size_) noexcept {
#ifdef _WIN32
    if (size_ == arena_size) {
      static MEM_ADDRESS_REQUIREMENTS req_{
        .LowestStartingAddress = nullptr,
        .HighestEndingAddress = nullptr,
        .Alignment = arena_size
      };

      static MEM_EXTENDED_PARAMETER param_{
        .Type = MemExtendedParameterAddressRequirements,
        .Pointer = &req_
      };

      return VirtualAlloc2(GetCurrentProcess(), nullptr, size_, MEM_RESERVE, PAGE_NOACCESS, &param_, 1);
    }

    return VirtualAlloc2(GetCurrentProcess(), nullptr, size_, MEM_RESERVE, PAGE_NOACCESS, nullptr, 0);
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
    if (size_ == arena_size) {
      const std::size_t resv_size_{ arena_size * 2 }; // Equates to 4 MB
      void* ptr_{ mmap(nullptr, resv_size_, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0) };

      if (ptr_ == MAP_FAILED) {
        return nullptr;
      }

      const std::uintptr_t base_{ reinterpret_cast<std::uintptr_t>(ptr_) };
      const std::uintptr_t aligned_{ (base_ + arena_size - 1) & ~(arena_size - 1) };
      const std::size_t pre_padding_{ aligned_ - base_ };
      const std::size_t post_padding_{ resv_size_ - pre_padding_ - arena_size };

      if (pre_padding_) {
        munmap(reinterpret_cast<void*>(base_), pre_padding_);
      }

      if (post_padding_) {
        munmap(reinterpret_cast<void*>(aligned_ + arena_size), post_padding_);
      }

      return reinterpret_cast<void*>(aligned_);
    }

    void* ptr_{ mmap(nullptr, size_, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0) };

    if (ptr_ == MAP_FAILED) {
      return nullptr;
    }

    return ptr_;
#endif // ^^^ _WIN32 ^^^
  }

  static inline bool commit_os(void* start_ptr_, const std::size_t size_) noexcept {
#ifdef _WIN32
    return VirtualAlloc2(GetCurrentProcess(), start_ptr_, size_, MEM_COMMIT, PAGE_READWRITE, nullptr, 0) != nullptr;
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
    return mprotect(start_ptr_, size_, PROT_READ | PROT_WRITE) == 0;
#endif // ^^^ _WIN32 ^^^
  }

  static inline bool decommit_os(void* start_ptr_, const std::size_t size_) noexcept {
#ifdef _WIN32
# pragma warning(push)
# pragma warning(disable : 6250 28160) // Suppress "results in address space leaks" false positive
    return VirtualFreeEx(GetCurrentProcess(), start_ptr_, size_, MEM_DECOMMIT) != 0;
# pragma warning(pop)
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
    madvise(start_ptr_, size_, MADV_DONTNEED);
    return mprotect(start_ptr_, size_, PROT_NONE) == 0;
#endif // ^^^ _WIN32 ^^^
  }

  static inline bool release_os(void* ptr_, const std::size_t size_) noexcept {
#ifdef _WIN32
    return VirtualFreeEx(GetCurrentProcess(), ptr_, 0, MEM_RELEASE) != 0;
#elifdef __linux__ // ^^^ _WIN32 / __linux__ vvv
    return munmap(ptr_, size_) == 0;
#endif // ^^^ _WIN32 ^^^
  }

  static inline void* alloc_pages(const std::size_t num_pages_) noexcept {
    arena* curr_{ arena_head_ }, * prev_{ nullptr };

    while (curr_) {
      std::size_t start_page_{}, consecutive_{};

      for (std::size_t i_{ 1 }; i_ < 512; ++i_) {
        const std::size_t block_idx_{ i_ / 64 };
        const std::size_t bit_idx_{ i_ % 64 };

        const std::uint64_t current_block_{ curr_->committed_pages_[block_idx_] };

        if (!(current_block_ & (std::uint64_t(1) << bit_idx_))) {
          if (!consecutive_) {
            start_page_ = i_;
          }

          ++consecutive_;

          if (consecutive_ == num_pages_) {
            void* commit_ptr_{ reinterpret_cast<std::byte*>(curr_) + (start_page_ << std::countr_zero(page_size)) };

            if (!commit_os(commit_ptr_, num_pages_ << std::countr_zero(page_size))) {
              return nullptr;
            }

            for (std::size_t j_{ start_page_ }; j_ < start_page_ + num_pages_; ++j_) {
              const std::size_t set_block_{ j_ / 64 };
              const std::size_t set_bit_{ j_ % 64 };
              curr_->committed_pages_[set_block_] |= (std::uint64_t(1) << set_bit_);
            }

            return commit_ptr_;
          }
        } else {
          consecutive_ = 0;
        }
      }

      arena* next_{ xor_ptrs(prev_, curr_->npx_) };
      prev_ = curr_;
      curr_ = next_;
    }

    arena* new_arena_{ reinterpret_cast<arena*>(reserve_os(arena_size)) };

    if (!new_arena_) {
      return nullptr;
    }

    if (!commit_os(new_arena_, page_size)) {
      if (!release_os(new_arena_, arena_size)) {
        // Memory leak!
      }

      return nullptr;
    }

    new(new_arena_) arena();

    for (std::size_t i_{}; i_ < 8; ++i_) {
      new_arena_->committed_pages_[i_] = 0;
    }

    new_arena_->committed_pages_[0] = 1;

    new_arena_->npx_ = xor_ptrs<arena>(nullptr, arena_head_);

    if (arena_head_) {
      arena_head_->npx_ = xor_ptrs<arena>(new_arena_, xor_ptrs<arena>(nullptr, arena_head_->npx_));
    }

    arena_head_ = new_arena_;

    void* commit_ptr_{ reinterpret_cast<std::byte*>(arena_head_) + page_size };

    if (!commit_os(commit_ptr_, num_pages_ << std::countr_zero(page_size))) {
      return nullptr;
    }

    for (std::size_t j_{ 1 }; j_ < 1 + num_pages_; ++j_) {
      const std::size_t set_block_{ j_ / 64 };
      const std::size_t set_bit_{ j_ % 64 };
      arena_head_->committed_pages_[set_block_] |= (std::uint64_t(1) << set_bit_);
    }

    return commit_ptr_;
  }

  static inline void free_pages(void* ptr_, const std::size_t num_pages_) noexcept {
    std::byte* byte_ptr_{ static_cast<std::byte*>(ptr_) };
    arena* curr_{ reinterpret_cast<arena*>(reinterpret_cast<std::uintptr_t>(ptr_) & ~(arena_size - 1)) };
    std::byte* arena_byte_ptr_{ reinterpret_cast<std::byte*>(curr_) };
    const std::size_t start_page_{ static_cast<std::size_t>(byte_ptr_ - arena_byte_ptr_) >> std::countr_zero(page_size) };

    if (decommit_os(ptr_, num_pages_ << std::countr_zero(page_size))) {
      for (std::size_t i_{ start_page_ }; i_ < start_page_ + num_pages_; ++i_) {
        const std::size_t block_idx_{ i_ / 64 };
        const std::size_t bit_idx_{ i_ % 64 };
        curr_->committed_pages_[block_idx_] &= ~(std::uint64_t(1) << bit_idx_);
      }

      bool is_empty_{ true };

      if (curr_->committed_pages_[0] != 1) {
        is_empty_ = false;
      } else {
        for (std::size_t i_{ 1 }; i_ < 8; ++i_) {
          if (curr_->committed_pages_[i_] != 0) {
            is_empty_ = false;
            break;
          }
        }
      }

      if (is_empty_) {
        arena* c_{ arena_head_ };
        arena* p_{ nullptr };

        while (c_) {
          arena* n_{ xor_ptrs(p_, c_->npx_) };

          if (c_ == curr_) {
            if (p_) {
              p_->npx_ = xor_ptrs<arena>(xor_ptrs<arena>(p_->npx_, c_), n_);
            } else {
              arena_head_ = n_;
            }

            if (n_) {
              n_->npx_ = xor_ptrs<arena>(p_, xor_ptrs<arena>(c_, n_->npx_));
            }

            break;
          }

          p_ = c_;
          c_ = n_;
        }

        if (release_os(curr_, arena_size)) {
          // Update counters in original code...
        } else {
          // Memory Leak!
        }
      }
    } else {
      // Memory leak!
    }
  }

#ifdef SELENA_ARENA_CLEANUP_ON_EXIT
  static inline void free_all() noexcept {
    arena* curr_{ arena_head_ }, * prev_{ nullptr };

    while (curr_) {
      arena* next_{ xor_ptrs<arena>(prev_, curr_->npx_) };

      if (!release_os(curr_, arena_size)) {
        // Memory leak!
      }

      prev_ = curr_;
      curr_ = next_;
    }

    arena_head_ = nullptr;

    large_allocs* curr_large_{ large_allocs_head_ };
    large_allocs* prev_large_{ nullptr };

    while (curr_large_) {
      large_allocs* next_large_{ xor_ptrs<large_allocs>(prev_large_, curr_large_->npx_) };

      if (!release_os(curr_large_, curr_large_->size_)) {
        // Memory leak!
      }

      prev_large_ = curr_large_;
      curr_large_ = next_large_;
    }

    large_allocs_head_ = nullptr;
  }

  static inline const int atexit_registry_{ std::atexit(free_all) };
#endif // SELENA_ARENA_CLEANUP_ON_EXIT
}; // class arena_alloc

} // namespace selena

#ifdef SELENA_ARENA_OVERLOAD_NEW_DELETE

#ifdef _WIN32
# pragma warning(push)
# pragma warning(disable : 28251)
#endif // _WIN32

void* operator new(const std::size_t size_) {
  void* ptr_{ selena::arena_alloc::alloc(size_) };

  if (!ptr_) {
    throw std::bad_alloc();
  }

  return ptr_;
}

void operator delete(void* ptr_) noexcept {
  selena::arena_alloc::free(ptr_);
}

void* operator new[](const std::size_t size_) {
  void* ptr_{ selena::arena_alloc::alloc(size_) };

  if (!ptr_) {
    throw std::bad_alloc();
  }

  return ptr_;
}

void operator delete[](void* ptr_) noexcept {
  selena::arena_alloc::free(ptr_);
}

void operator delete(void* ptr_, std::size_t) noexcept {
  selena::arena_alloc::free(ptr_);
}

void operator delete[](void* ptr_, std::size_t) noexcept {
  selena::arena_alloc::free(ptr_);
}

#ifdef _WIN32
# pragma warning(pop)
#endif // _WIN32

#endif // SELENA_ARENA_OVERLOAD_NEW_DELETE

#endif // SELENA_ARENA_ALLOC

int speed_{ [] {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}() };

class Solution {
public:
  static bool isValid(const std::string& str) {
    if (str.empty()) {
      return false;
    }

    if (str.length() == 1) {
      return false;
    }

    std::stack<char> temp{};
    for (const char ch : str) {
      switch (ch) {
        case ')':
        case '}':
        case ']':
          if (temp.empty()) {
            return false; 
          }
          
          if (temp.top() != pair(ch)) {
            return false;
          }
          
          temp.pop();
          break;
        default: {
          temp.push(ch);
        }
      }
    }

    return temp.empty();
  }

private:
  static inline char pair(const char c) {
    switch (c) {
      case ')': {
        return '(';
      }
      case '}': {
        return '{';
      }
      case ']': {
        return '[';
      }
      default: {
        return '0';
      }
    }
  }
};