#include <vector>
#include <algorithm>
#include <stdexcept>

class Solution {
private:
    std::vector<int> trackTakenItems(std::vector<std::vector<int>>& finalValues, std::vector<int>& wt) {
        if (finalValues.size() != wt.size() + 1)
            throw std::runtime_error("The number of rows of 2D vector \"finalValues\" must be greater exactly by one than the size of 1D vector \"wt\"");

        std::vector<int> path{};

        size_t row{ finalValues.size() - 1 };
        size_t col{ finalValues[0].size() - 1 };

        while (row > 0 && col > 0) {
            int currItemID{ row - 1 };
            if (finalValues[row][col] != finalValues[row - 1][col]) {
                // This means that the item with ID == row - 1 was included
                path.push_back(currItemID);
                int weightOfIncludedItem{ wt[currItemID] };
                col -= weightOfIncludedItem;
            }

            row--;
        }

        std::reverse(path.begin(), path.end()); // #include <algorithm>    
        return path;
    }

public:
    int knapsack(int W, std::vector<int>& val, std::vector<int>& wt) {
        const size_t n{ val.size() };
        if (n != wt.size())
            throw std::runtime_error("Vectors \"val\" and \"wt\" must have the same size");

        /**
         * Tabulation
         * ROWS: item IDs (row 0 represents no items (EMPTY), row 1 represents item 0 etc.)
         * COLUMNS: knapsack capacity (W)
         *
         * Initially, there are 0's in the first row
         * (since that row represents lack of items)
         * and the first column
         * (since we cannot take any items with capacity 0).
         */
        std::vector<std::vector<int>> finalValues(n + 1, std::vector<int>(W + 1, 0));

        for (int i{ 1 }; i < static_cast<int>(n + 1); i++) {
            for (int j{ 1 }; j < W + 1; j++) {
                /**
                 * CAUTION:
                 * - Row 0 represents no items
                 * - Row i represents item i-1
                 *
                 * Select the maximum value out of the following:
                 * a) the value if we leave out item i-1 => equal to the value directly above
                 * b) the value if we take item i-1 (if the capacity allows that)
                 * => equal to the value from row i-1 and column j-w[i-1]
                */
                int currItemID{ i - 1 };

                finalValues[i][j] = finalValues[i - 1][j]; // Case (a)
                int valueIfTaken;
                if (
                    j - wt[currItemID] >= 0
                    && (valueIfTaken = finalValues[i - 1][j - wt[currItemID]] + val[currItemID]) > finalValues[i][j]
                    ) {
                    finalValues[i][j] = valueIfTaken; // Case (b)
                }
            }
        }

        // Print the taken items

        // for (const int &el : trackTakenItems(finalValues, wt))
        //     std::cout << el << " ";
        // std::cout << std::endl;

        return finalValues[n][W];
    }
};