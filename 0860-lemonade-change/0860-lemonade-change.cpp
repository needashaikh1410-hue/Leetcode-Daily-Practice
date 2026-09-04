class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0;
        int ten = 0;

        for (int bill : bills) {
            // Case 1: Customer pays with $5 bill (No change needed)
            if (bill == 5) {
                five++;
            }
            // Case 2: Customer pays with $10 bill (Needs $5 change)
            else if (bill == 10) {
                if (five == 0) return false;
                five--;
                ten++;
            }
            // Case 3: Customer pays with $20 bill (Needs $15 change)
            else {
                // Prefer giving $10 + $5 to save $5 bills for future customers
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                }
                // Fallback to giving three $5 bills
                else if (five >= 3) {
                    five -= 3;
                }
                // Cannot provide change
                else {
                    return false;
                }
            }
        }

        return true;
    }
};