#include <vector> // std::vector<>

class Solution {
private:
    std::vector<int> savedArr;
    std::vector<std::vector<int>> memo; // -1 - result not found, 0 - result is false, 1 - result is true
    std::vector<std::vector<bool>> dp2d;
    std::vector<bool> dp1d;

    // Naive approach: O(2^N * N) / O(N) (time complexity / space complexity)
    bool brute(int i, int sum) {
        // Check all possible subsets.
        //   For a given subset, check if all its values add up to sum.
        //     If they don't, move on to the next subset.
        //     If they do, return TRUE.
        // If TRUE was not returned for any subset, return FALSE.

        // Base cases
        if (sum == 0) return true;
        if (i == 0) return savedArr[0] == sum;

        // Recursion
        bool res{ false };

        // Consider the case when we don't take the element
        res = res || brute(i - 1, sum);

        if (savedArr[i] <= sum) {
            // If the element can be taken to the sum, consider the case when we do so
            res = res || brute(i - 1, sum - savedArr[i]);
        }

        return res;
    }

    // Top-Down Dynamic Programming Approach: O(N^2) / O(N^2)
    int td(int i, int sum) {
        // Proceed like in brute force, but cache the sub-problem results.

        // Base cases
        if (sum == 0) return 1;
        if (i == 0) return savedArr[0] == sum ? 1 : 0;

        // Check cache
        if (memo[i][sum] != -1)
            return memo[i][sum];

        // Recursion results
        int caseIfTaken{ 0 }, caseIfNotTaken{ 0 };

        // Consider the case when we don't take the element
        caseIfNotTaken = td(i - 1, sum) == 1;

        if (savedArr[i] <= sum) {
            // If the element can be taken to the sum, consider the case when we do so
            caseIfTaken = td(i - 1, sum - savedArr[i]);
        }

        return memo[i][sum] = (caseIfTaken == 1 || caseIfNotTaken == 1 ? 1 : 0);
    }

    bool tdDriver(int n, int sum) {
        memo = std::vector<std::vector<int>>(
            n,
            std::vector<int>(sum + 1, -1)
        );
        return td(n - 1, sum) == 1;
    }

    // Bottom-Up Dynamic Programming Approach: O(N^2) / O(N^2)
    bool bu(int n, int sum) {

        // dp2d[m][sum] - can we reach sum by taking elements from savedArr[0:m]?
        dp2d = std::vector<std::vector<bool>>(
            n + 1,
            std::vector<bool>(sum + 1, false)
        );

        // We cannot reach sum with no items, unless sum == 0
        for (int i{}; i < n + 1; i++)
            dp2d[i][0] = true;

        for (int m{ 1 }; m < n + 1; m++) {
            for (int currSum{ 1 }; currSum < sum + 1; currSum++) {
                // Leave or (if possible) take element savedArr[m-1];
                bool caseIfNotTaken{ dp2d[m - 1][currSum] }, caseIfTaken{ false };

                if (savedArr[m - 1] <= currSum) {
                    caseIfTaken = dp2d[m - 1][currSum - savedArr[m - 1]];
                }
                dp2d[m][currSum] = caseIfNotTaken || caseIfTaken;
            }
        }


        return dp2d[n][sum];
    }

    // Bottom-Up Space-Optimised Dynamic Programming Approach: O(N^2) / O(N)
    bool buSpace(int n, int sum) {
        dp1d = std::vector<bool>(sum + 1, false);

        // We cannot reach sum with no items, unless sum == 0
        dp1d[0] = true;

        for (int m{ 1 }; m < n + 1; m++) {
            for (int currSum{ sum }; currSum >= savedArr[m - 1]; currSum--) {
                // Leave or (if possible) take element savedArr[m-1];
                bool caseIfNotTaken{ dp1d[currSum] }, caseIfTaken{ dp1d[currSum - savedArr[m - 1]] };
                dp1d[currSum] = caseIfNotTaken || caseIfTaken;
            }
        }


        return dp1d[sum];
    }

public:
    bool isSubsetSum(std::vector<int>& arr, int sum) {
        savedArr = arr;
        int n{ static_cast<int>(arr.size()) };

        // return brute(n - 1, sum);
        // return tdDriver(n, sum);
        // return bu(n, sum);
        return buSpace(n, sum);
    }
};
