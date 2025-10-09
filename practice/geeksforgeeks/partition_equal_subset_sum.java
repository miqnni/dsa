import java.util.Arrays;
import java.util.Set;
import java.util.HashSet;

class Solution {
    static boolean hashSetSolution(int arr[]) {
        int sumNums = Arrays.stream(arr).sum();
        if (sumNums % 2 == 1)
            return false;
        
        Set<Integer> reachedSums = new HashSet<>();
        int targetSum = sumNums / 2;
        
        // First partition: after the last element.
        reachedSums.add(0);
        
        for (int i = arr.length - 1; i >= 0; i--) {
            Iterator<Integer> reachedSumsIterator = reachedSums.iterator();
            Set<Integer> reachedSumsExtension = new HashSet<>();
            
            while(reachedSumsIterator.hasNext()) {
                int setEl = reachedSumsIterator.next();
                reachedSumsExtension.add(setEl + arr[i]);
                reachedSumsExtension.add(setEl);
            }
            
            reachedSums = reachedSumsExtension;
        }
        
        return reachedSums.contains(targetSum);
    }
    
    static boolean booleanArraySolution(int arr[]) {
        int sumNums = Arrays.stream(arr).sum();
        
        // An even better optimisation
        if ((sumNums & 1 /* 10101101 & 00000001 == 00000001 */) == 1)
            return false;
            
        int targetSum = sumNums / 2;
        boolean isSumReached[] = new boolean[targetSum + 1];
        isSumReached[0] = true;
        
        for (int arrEl : arr) {
            // We want to use each element only once,
            // so we go backwards.
            for (int inspectedSum = targetSum; inspectedSum >= arrEl; inspectedSum--) {
                // It's like we're trying to create one subset
                // with sum equal to sumNums / 2.
                // We either take a number (arrEl) to the subset or not.
                isSumReached[inspectedSum] = isSumReached[inspectedSum] || isSumReached[inspectedSum - arrEl];
            }
            
            // Early Exit
            if (isSumReached[targetSum])
                return true;
        }
        
        return isSumReached[targetSum];
    }
    
    static boolean bitSetSolution(int arr[]) {
        return false; // TODO
    }
    
    static boolean equalPartition(int arr[]) {
        return booleanArraySolution(arr);
    }
}