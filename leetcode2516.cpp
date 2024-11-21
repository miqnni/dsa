#include <iostream>
#include <string>
#include <vector>
#include <map>

class Solution {
private:
    bool constraintMet(const std::map<char, int>& counter, const int& k) {
        for (const auto& entry : counter) {
            if (entry.second < k)
                return false;
        }
        return true;
    }

    void printCounter(const std::map<char, int>& counter) {
        for (const auto& entry : counter) {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }
    }

public:
    int takeCharacters(std::string s, int k) {

        std::map<char, int> counter{
            {'a', 0},
            {'b', 0},
            {'c', 0}
        };

        int n{ static_cast<int>(s.size()) };
        int leftIdx{}; // The Removal Window starts between leftIdx and leftIdx + 1.
        int rightIdx{ n - 1 };  // The Removal Window ends between rightIdx and rightIdx + 1.
        // CHARACTER REMOVED == CHARACTER NOT TAKEN.

        // Move the leftIdx through the whole string and count all chars.
        for (; leftIdx < n; leftIdx++) {
            counter[s[leftIdx]]++;
        }
        if (!constraintMet(counter, k))
            return -1;
        int minCharsTaken{ leftIdx /* equal to n */ }; // We start with Removal Window size 0.
        leftIdx--; // now equal to n - 1 (no index-out-of-bounds error/exception)
        // std::cout << "L: " << leftIdx << ", R: " << rightIdx << std::endl;

        while (leftIdx >= 0) {
            while (!constraintMet(counter, k) && leftIdx <= rightIdx) {
                // If the constraint is not met, narrow the Removal Window down
                // by moving rightIdx to the left (as long as it's possible: condition L <= R).
                // Be sure to update the counter in the meantime (count the newly-included char).

                counter[s[rightIdx]]++;
                rightIdx--;
                // std::cout << "L: " << leftIdx << ", R: " << rightIdx << std::endl;

            }
            if (n - (rightIdx - leftIdx) < minCharsTaken)
                minCharsTaken = n - (rightIdx - leftIdx);

            // Let's slide leftIdx to the left and update the counter.
            counter[s[leftIdx]]--; // We 
            leftIdx--;
            // std::cout << "L: " << leftIdx << ", R: " << rightIdx << std::endl;

            // Since the RW (= Removal Window) has increased
            // (more chars removed <=> fewer chars taken),
            // let's check the constraint
            // and if it's met, it might be necessary to update minCharsTaken.
            if (constraintMet(counter, k) && n - (rightIdx - leftIdx) < minCharsTaken)
                minCharsTaken = n - (rightIdx - leftIdx);

        }

        return minCharsTaken;

    }

};