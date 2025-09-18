// LEETCODE 5
// USING DYNAMIC PROGRAMMING

#include <string> // std::string
#include <vector> // std::vector<>

class Solution {
public:
    std::string longestPalindrome(std::string& s) {
        // dp[i][j] - is the substring s[i:j+1] a palindrome?
        int n{ static_cast<int>(s.length()) };

        std::vector<std::vector<bool>> dp(n,
            std::vector<bool>(n, false)
        );

        // The first length 1 palindrome is the first char
        int maxPalLen{ 1 };
        int maxPalStartIdx{ 0 };

        // Base cases
        for (int i{}; i < n - 1; i++) {
            dp[i][i] = true; // A single char is always a palindrome
            if (s[i] == s[i + 1]) { // Two consecutive chars can form a palindrome
                dp[i][i + 1] = true;
                if (maxPalLen == 1) {
                    // If this is the first found palindrome of length 2,
                    // save its starting index (because if we don't find longer palindromes,
                    // we want to return the first occurrence of length 2 palindrome)
                    maxPalStartIdx = i;
                    maxPalLen = 2;
                }
            }
        }
        dp[n - 1][n - 1] = true;

        // If we know that dp[i][j] == true,
        // then we can find dp[i-1][j+1] by expanding the palindrome
        // in both directions.

        // If we know that dp[i][j] == false,
        // then dp[i-1][j+1] is also false, because expanding a non-palindrome
        // in both directions will never turn it into a palindrome.
        // (No need to update dp, because false is the default value.)

        // We move diagonally from top left to bottom right, starting from
        // dp[0][2] -> dp[n-3][n-1] (incl.)
        // dp[0][3] -> dp[n-4][n-1]
        // ...
        // dp[0][startJ] -> dp[n-1-startJ][n-1]
        // ...
        // dp[0][n-1] -> dp[0][n-1] (single, top right cell)
        //
        // NOTICE THAT palindromeLength = startJ + 1
        for (int startJ{ 2 }; startJ < n; startJ++) {
            for (int i{ 0 }; i < (n - startJ); i++) {
                int j{ startJ + i };
                if (dp[i + 1][j - 1] && s[i] == s[j]) {
                    // We expand an existing palindrome.
                    dp[i][j] = true;
                    int palLen{ startJ + 1 };

                    // If the record of length has been broken,
                    // save the occurrence.
                    if (palLen > maxPalLen) {
                        maxPalLen = palLen;
                        maxPalStartIdx = i;
                    }
                }
            }
        }

        return s.substr(maxPalStartIdx, maxPalLen);
    }
};