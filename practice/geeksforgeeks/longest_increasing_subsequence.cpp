// Time O(N^2), space O(N)
// DP Tabulation

class Solution {
  public:
    int lis(std::vector<int>& arr) {
        const size_t n = arr.size();
        std::vector<int> lisEndingAt(n, 1);
        int maxLisVal = 1;
        
        for (int i{1}; i < n; i++) {
            int currLisVal = 1;
            
            // Add 1 to the value of lisEndingAt[j] where arr[j] < arr[i].
            // Take the maximum of those obtained values.
            for (int j{}; j < i; j++) {
                if (arr[j] < arr[i]) {
                    currLisVal = lisEndingAt[j] + 1 > currLisVal ? lisEndingAt[j] + 1 : currLisVal;
                }
            }
            
            maxLisVal = currLisVal > maxLisVal ? currLisVal : maxLisVal;
            lisEndingAt[i] = currLisVal;
        }
        
        return maxLisVal;
    }
};