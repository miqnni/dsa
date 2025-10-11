// LEETCODE 2824

import java.util.Arrays;
import java.util.List;
import java.util.Collections;

class SolutionLeetCode {
    public int countPairs(List<Integer> nums, int target) {
        // Sort the array.
        Collections.sort(nums);
        
        // Create two pointers.
        int l = 0, r = nums.size() - 1;
        
        int pairCounter = 0;
        
        while (l < r) {
            // If the sum is too large, decrease the right pointer.
            if (nums.get(l) + nums.get(r) >= target) {
                r --;
                continue;
            }
            
            // Else: (1) count the pairs with fixed left pointer and the right pointer moving
            // all the way down to the left pointer (excl.).
            pairCounter += r - l;
            
            // (2) move the left pointer up and check if any pairs can be found
            // when it's been increased.
            l++;
        }
        
        return pairCounter;
    }
}

class SolutionGeeksForGeeks {
    int countPairs(int arr[], int target) {
        // Sort the array.
        Arrays.sort(arr);
        
        // Create two pointers.
        int l = 0, r = arr.length - 1;
        
        int pairCounter = 0;
        
        while (l < r) {
            // If the sum is too large, decrease the right pointer.
            if (arr[l] + arr[r] >= target) {
                r --;
                continue;
            }
            
            // Else: (1) count the pairs with fixed left pointer and the right pointer moving
            // all the way down to the left pointer (excl.).
            pairCounter += r - l;
            
            // (2) move the left pointer up and check if any pairs can be found
            // when it's been increased.
            l++;
        }
        
        return pairCounter;
    }
}
