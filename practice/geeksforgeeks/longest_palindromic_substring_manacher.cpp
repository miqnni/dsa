// LEETCODE 5
// USING MANACHER'S ALGORITHM

#include <string> // std::string
#include <vector> // std::vector<>
#include <algorithm> // std::min

class Solution {
private:
    std::string processStrForManacher(std::string& s) {
        std::string resStr{ "#" };

        for (const char& ch : s) {
            resStr += ch;
            resStr += "#";
        }

        return resStr;
    }

public:
    std::string longestPalindrome(std::string& s) {
        std::string procS{ processStrForManacher(s) };

        int n{ static_cast<int>(procS.length()) };
        std::vector<int> palValues(n, 0);

        int centre{ 0 }, right{ 0 };

        // Main loop of Manacher's Algorithm
        for (int i{}; i < n; i++) {
            int mirrorVal{ 2 * centre - i };

            if (i < right) {
                palValues[i] = std::min(right - i, palValues[mirrorVal]);
            }
            else {
                palValues[i] = 0;
            }

            // Expand the palindrome with a centre under i-th index
            while (
                i + 1 + palValues[i] < n &&
                i - 1 - palValues[i] >= 0 &&
                procS[i + 1 + palValues[i]] == procS[i - 1 - palValues[i]]
                ) {
                palValues[i]++;
            }

            // If `right` can be updated (i.e. taken farther to the right), update it along with centre
            if (i + palValues[i] > right) {
                centre = i;
                right = i + palValues[i];
            }
        }

        // Extract the maximum value of palValues and its index
        int maxPalLen{ 0 }, centreIdx{ 0 };
        for (int i{}; i < n; i++) {
            int palLen = palValues[i];
            if (palLen > maxPalLen) {
                maxPalLen = palLen;
                centreIdx = i;
            }
        }

        int maxPalStartIdx{ (centreIdx - maxPalLen) / 2 };

        return s.substr(maxPalStartIdx, maxPalLen);
    }
};
