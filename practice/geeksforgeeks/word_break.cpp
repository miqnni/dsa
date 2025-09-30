// LEETCODE 139

#include <vector> // std::vector<>
#include <string> // std::string

class Solution {
public:
    bool wordBreak(std::string& s, std::vector<std::string>& dictionary) {
        int n{ static_cast<int>(s.length()) };
        std::vector<bool> dp(n + 1, false);

        dp[n] = true; // Base case


        for (int i{ n - 1 }; i >= 0; i--) {
            for (std::string w : dictionary) {
                if (w.length() > n - i)
                    continue;

                if (s.substr(i, w.length()) == w) {
                    // If this condition is met, get the dp[] value for the fragment
                    // AFTER the occurrence of word `w` in `s`.
                    dp[i] = dp[i + w.length()]; // the If (w.length() ...) statement ensures no out-of-bounds error
                }

                // If you found one way to break down s[i:],
                // finding more does not change anything.
                if (dp[i])
                    break;
            }
        }

        return dp[0];
    }
};
