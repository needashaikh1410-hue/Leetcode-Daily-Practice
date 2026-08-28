class LFUCache {
private:
    struct Node{
        int key;
        int value;
        int freq;
        Node *next;
        Node *prev;
        Node(int k,int v): key(k),value(v),freq(1),prev(nullptr),next(nullptr){}
    };
    struct List{
        int size;
        Node * head;
        Node * tail;

        List(){
            size=0;
            head=new Node(0,0);
            tail=new Node(0,0);
            tail->prev=head;
            head->next=tail;
        }
        void addNode(Node * new_node){
            Node* temp=head->next;
            head->next=new_node;
            new_node->next=temp;
            temp->prev=new_node;
            new_node->prev=head;
            size++;
        }

        void deleteNode(Node * del_node){
            del_node->prev->next=del_node->next;
            del_node->next->prev=del_node->prev;
            del_node->next=nullptr;
            del_node->prev=nullptr;
            size--;
        }
    };
    
    unordered_map<int,Node*> key_node;
    unordered_map<int,List*> freq_node;
    void updatefreqnode(Node * node){
        freq_node[node->freq]->deleteNode(node);
        if(node->freq==minfreq && freq_node[node->freq]->size==0){
            minfreq+=1;
        }
        node->freq+=1;
        if(freq_node.find(node->freq)==freq_node.end()){
            freq_node[node->freq]=new List();
        }
        freq_node[node->freq]->addNode(node);

    }
    int cap;
    int minfreq;
public:
    LFUCache(int capacity) {
        cap=capacity;
        minfreq=0;
    }
    
    int get(int key) {
        if (key_node.find(key)==key_node.end())
            return -1;
        Node* node = key_node[key];
        updatefreqnode(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if(cap==0){return;}
        if(key_node.find(key)!=key_node.end()){
            Node * node= key_node[key];
            node->value=value;
            updatefreqnode(node);
            return;
        }

        if(key_node.size()==cap){
            List * minlist=freq_node[minfreq];
            Node * LRU=minlist->tail->prev;
            key_node.erase(LRU->key);
            minlist->deleteNode(LRU);
            delete LRU;
        }
        minfreq=1;
        if(freq_node.find(minfreq)==freq_node.end()){
            freq_node[minfreq]=new List();
        }
        Node * new_node= new Node(key,value);
        freq_node[minfreq]->addNode(new_node);
        key_node[key]=new_node;

    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */