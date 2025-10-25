class Solution {
    public int findMaxSum(int arr[]) {
        int dp[] = new int[arr.length + 1]; // Initialize an array of a given length. Elements are initialized with zero value
        
        // dp[i] -- Maximum loot from arr[:i]
        // How to calculate dp[i]:
        // - Option 1 -- take item arr[i-1], assuming that arr[i-2] is not taken
        // - Option 2 -- don't take item arr[i-1]
        // - dp[i] = max(option1, option2)
        // dp[i] = max(dp[i-2] + arr[i-1], dp[i-1]);
        
        // Base cases
        if (arr.length < 1)
            return 0;
        dp[0] = 0; // No loot from an empty array
        
        if (arr.length == 1)
            return arr[0];
        dp[1] = arr[0]; // Only 1 house to loot from
        
        
        // Dynamic Programming Bottom-Up
        for (int i = 2; i < dp.length; i++) {
            
            // Concerns the item arr[i-1]
            int lootAfterTakingTheItem = dp[i-2] + arr[i-1];
            int lootAfterLeavingTheItem = dp[i-1];
            
            dp[i] = Math.max(lootAfterTakingTheItem, lootAfterLeavingTheItem);
        }
        
        return dp[arr.length]; // The result for the whole array `arr`
    }
}
