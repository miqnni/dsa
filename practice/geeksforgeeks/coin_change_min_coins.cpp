#include <vector> // std::vector<>
#include <limits> // std::numeric_limits<>
#include <algorithm> // std::min()

class Solution {
private:
    static const int inf{ std::numeric_limits<int>::max() };

    std::vector<int> savedCoins;
    std::vector<std::vector<int>> dp;

    int topDownInner(int numCoins, int sum) {
        // Base cases
        if (sum == 0) return 0; // We don't have to take any coins, so the min number of coins is 0
        if (numCoins == 0) return inf; // Provided that sum != 0, we can't reach the sum with no coins
        if (sum < 0) return inf; // We can never reach a negative sum

        // Memo
        if (dp[numCoins][sum] != inf)
            return dp[numCoins][sum];

        // Recursion; Save the result to memo and return it
        int valueIfTaken{ topDownInner(numCoins, sum - savedCoins[numCoins - 1]) };
        valueIfTaken = (valueIfTaken == inf) ? inf : valueIfTaken + 1; // Protection against overflowing max int

        int valueIfNotTaken{ topDownInner(numCoins - 1, sum) };

        return dp[numCoins][sum] = std::min(
            valueIfTaken, // Take coin i-1
            valueIfNotTaken // Leave coin i-1 and move to the coin i-2
        );
    }

    int topDown(int numCoins, int sum) {
        dp = std::vector<std::vector<int>>(
            numCoins + 1,
            std::vector<int>(sum + 1, inf)
        );

        int res{ topDownInner(numCoins, sum) };
        return res == inf ? -1 : res;
    }

    int bottomUp(int numCoins, int sum) {
        std::vector<int> dp1d(sum + 1, inf);

        dp1d[0] = 0; // Zero coins needed to make sum == 0

        for (const int& coin : savedCoins) {
            for (int currSum = coin; currSum <= sum; currSum++) {
                int valueFromPrevCoins{ dp1d[currSum] };

                int valueIfCoinTaken{ dp1d[currSum - coin] };
                valueIfCoinTaken = (valueIfCoinTaken == inf) ? inf : valueIfCoinTaken + 1; // Protection against overflowing max int

                dp1d[currSum] = std::min(valueFromPrevCoins, valueIfCoinTaken);
            }
        }

        // for (auto el : dp1d) std::cout << (el == inf ? -1 : el)  << " ";

        return dp1d[sum] == inf ? -1 : dp1d[sum];
    }


public:
    int minCoins(std::vector<int>& coins, int sum) {
        // code here
        savedCoins = coins;
        int numCoins{ static_cast<int>(coins.size()) };

        // return topDown(numCoins, sum); // TLE
        return bottomUp(numCoins, sum);
    }
};