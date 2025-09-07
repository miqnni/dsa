#include <vector> // std::vector
#include <algorithm> // std::max

class Solution {
public:
    int knapSack(std::vector<int>& val, std::vector<int>& wt, int capacity) {
        int n{ static_cast<int>(val.size()) };
        std::vector<std::vector<int>> finalValues(
            n + 1,
            std::vector<int>(capacity + 1, 0)
        );

        for (int i{ 1 }; i < n + 1; i++) {
            for (int j{ 1 }; j < capacity + 1; j++) {
                // We are considering item i - 1: we can take it once
                // (if capacity allows that)
                // and face the same dillema again or leave it out
                // and move on to the next item.

                int valueIfNotTaken{ finalValues[i - 1][j] };
                int valueIfTaken{};
                if (wt[i - 1] <= j) {
                    // Take the item i-1 WITHOUT moving to the next one.
                    valueIfTaken = finalValues[i /* NOT: i-1 */][j - wt[i - 1]] + val[i - 1];
                }
                finalValues[i][j] = std::max(valueIfNotTaken, valueIfTaken);
            }
        }

        return finalValues[n][capacity];
    }
};