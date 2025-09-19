#include <vector> // std::vector<>
#include <algorithm> // std::min_element(), std::ranges::min_element()

#define BOTTOM_UP

class Solution {
private:
    std::vector<int> savedCoins;
    // int lowestCoin;

    // dp[i][j] - the number of ways we can take coins from coins[:i] if remaining sum is j
    std::vector<std::vector<int>> dp;

    // SOLUTION 1: Top-down approach (memoisation)

    int takeOrLeaveTheCoin(int numOfCoins, int remainingSum) {

        // Base cases
        if (remainingSum == 0) return 1;
        if (remainingSum < 0) return 0;
        if (numOfCoins == 0) return 0;

        // Check cache
        if (dp[numOfCoins][remainingSum] != -1)
            return dp[numOfCoins][remainingSum];

        // Recursion
        int ways{
            takeOrLeaveTheCoin(numOfCoins, remainingSum - savedCoins[numOfCoins - 1]) // take (n-1)-th coin
            + takeOrLeaveTheCoin(numOfCoins - 1, remainingSum) // leave (n-1)-th coin forever
        };

        // Update cache and return result
        dp[numOfCoins][remainingSum] = ways;
        return ways;

    }

    int solveTopDown(int sum) {
        dp = std::vector<std::vector<int>>(
            savedCoins.size() + 1,
            std::vector<int>(sum + 1, -1)
        );

        return takeOrLeaveTheCoin(savedCoins.size(), sum);
    }

    // SOLUTION 2: Bottom-up approach (tabulation)
    int solveBottomUp(int sum) {
        dp = std::vector<std::vector<int>>(
            savedCoins.size() + 1,
            std::vector<int>(sum + 1, 0)
        );

        // Fill the first column with 1 (because if we need to collect
        // sum == 0, there is only one way: do nothing)
        for (int i{}; i < dp.size(); i++)
            dp[i][0] = 1;

        // Tabulation
        for (int i{ 1 }; i < dp.size(); i++) {
            for (int j{ 1 }; j < dp[0].size(); j++) {
                int waysIfCoinNotTaken{ dp[i - 1][j] }; // applies to coin i-1
                dp[i][j] = waysIfCoinNotTaken;

                if (j >= savedCoins[i - 1]) {
                    int waysIfCoinTaken{ dp[i][j - savedCoins[i - 1]] }; // applies to coin i-1
                    dp[i][j] += waysIfCoinTaken;
                }
            }
        }

        return dp[savedCoins.size()][sum];
    }



public:
    int count(std::vector<int>& coins, int sum) {
        savedCoins = coins;

        // lowestCoin = *std::min_element(coins.begin(), coins.end());
        // OR
        // lowestCoin = std::ranges::min_element(coins); // C++20

#ifdef BOTTOM_UP
        return solveBottomUp(sum);
#else
        return solveTopDown(sum);
#endif // BOTTOM_UP
    }
};