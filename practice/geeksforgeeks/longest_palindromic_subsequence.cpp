// This solution: DP T-D
// Alt. solution: Run LCS(s. s[::-1])

#include <string> // std::string
#include <algorithm> // std::max()
#include <vector> // std::vector<>

class Solution {
private:
    std::vector<std::vector<int>> memo;

    // T-D
    int lpsConsiderStringRange(std::string& s, int pL, int pR) {
        // Base case
        if (pL < 0 || pR >= s.length())
            return 0;

        // Memo
        if (memo[pL][pR] != -1)
            return memo[pL][pR];

        // Case: matching chars under indices
        if (s[pL] == s[pR]) {
            int startingLength{ 1 }; // Case: we start expanding range from a single character 

            // Case: we either start expanding range from a pair of adjacent matching characters
            // or we continue expanding the range and because the characters match, we do it in both ways
            if (pL != pR)
                startingLength = 2;

            // Expand in both ways
            return memo[pL][pR] = startingLength + lpsConsiderStringRange(s, pL - 1, pR + 1);
        }

        // Case: different chars under indices => expand either left or right
        return memo[pL][pR] = std::max(
            lpsConsiderStringRange(s, pL - 1, pR),
            lpsConsiderStringRange(s, pL, pR + 1)
        );
    }

    // B-U
    // ...

public:
    int longestPalinSubseq(std::string& s) {
        int maxPalinLen{ 1 };

        memo = std::vector<std::vector<int>>(
            s.length(),
            std::vector<int>(s.length(), -1)
        );

        // T-D
        for (int i{}; i < s.length() - 1; i++) {
            // Expand from a single char to form an odd-length palindrome
            maxPalinLen = std::max(maxPalinLen, lpsConsiderStringRange(s, i, i));


            // Expand from a pair of chars to form an even-length palindrome.
            // The chars need not to be equal, because we don't have to consider
            // ALL chars of s[i:j+1] to be a part of a palindrome.
            maxPalinLen = std::max(maxPalinLen, lpsConsiderStringRange(s, i, i + 1));
        }

        // B-U

        return maxPalinLen;
    }
};