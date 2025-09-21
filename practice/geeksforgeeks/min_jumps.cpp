// LEETCODE 45 - Jump Game II

#include <limits> // std::numeric_limits<>
#include <vector> // std::vector<>
#include <algorithm> // std::min(), std::max()

class Solution {
private:
    const int inf{ std::numeric_limits<int>::max() };

    int minJumpsNaiveDP(std::vector<int>& arr) { // O(N^2)
        int n{ static_cast<int>(arr.size()) };
        std::vector<int> dp(n, inf);
        dp[0] = 0; // No jumps needed to reach arr[0].

        for (int jumpFrom{}; jumpFrom < n - 1; jumpFrom++) {
            if (dp[jumpFrom] == inf)
                return -1; // If the current element is unreachable, then all its subsequent element are also unreachable.

            for (int reachedPos{ jumpFrom + 1 }; reachedPos < std::min(n, jumpFrom + arr[jumpFrom] + 1); reachedPos++) {
                dp[reachedPos] = std::min(dp[reachedPos], dp[jumpFrom] + 1);
            }
        }

        // for (auto el : dp) std::cout << el << " ";
        return dp[n - 1] == inf ? -1 : dp[n - 1];
    }

public:
    int minJumps(std::vector<int>& arr) { // Greedy (simplified BFS), O(N)
        int n{ static_cast<int>(arr.size()) };

        int res{}, sectionStart{}, sectionEnd{}; // Section: the part of the array that we can reach in exactly x steps. Section end inclusive

        while (sectionEnd < n - 1) {
            int nextSectionEnd{ sectionEnd };

            // Find the end of the next section
            for (int idxInSection{ sectionStart }; idxInSection < sectionEnd + 1; idxInSection++) {
                int maxReachableIdx{ idxInSection + arr[idxInSection] };
                nextSectionEnd = std::max(nextSectionEnd, maxReachableIdx);
            }

            // If the next section's end isn't larger than the current one's, it means there is no next section.
            // Since the current section's end is NOT n - 1 (that's the while loop condition),
            // the final index is unreachable.
            if (nextSectionEnd <= sectionEnd)
                return -1;

            // Update section boundaries
            sectionStart = sectionEnd + 1;
            sectionEnd = nextSectionEnd;

            // Update result with the next section's number
            res++;
        }

        return res;
    }
};
