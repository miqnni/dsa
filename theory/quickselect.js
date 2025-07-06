class Solution {
    /**
     * Select a pivot index in the array.
     * Then move the elements with smaller values than the value under pivot to the left of the array.
     * Finally, swap the pivot with the first element that is not considered smaller than its value.
     * The resulting position of the pivot is the same as it would be in a sorted array -> useful for QuickSelect.
     * @param  {Array}  arr   The array which we operate on. We consider only the fragment in the interval [left, right)
     * @param  {Number} left  The index of the lower bound (INCLUSIVE) of the array fragment we operate on
     * @param  {Number} right The index of the upper bound (NON-INCLUSIVE) of the array fragment we operate on
     */
    static partition(arr, left, right) {
        // let initialPivotLoc = left + Math.floor(Math.random() * (right - left));
        let initialPivotLoc = left + Math.floor((right - left) / 2);
        console.log("-- pivot: " + initialPivotLoc); // DEBUG
        let pivotVal = arr[initialPivotLoc];
        let finalPivotLoc = left; // The variable which eventually will contain the pivot's final location

        for (let i = left; i < right; i++) {
            if (arr[i] < pivotVal) {
                // Swap so that the element smaller than the pivot's value goes to the left
                let tmp = arr[i];
                arr[i] = arr[finalPivotLoc];
                arr[finalPivotLoc] = tmp;
                finalPivotLoc++;
            }
        }

        // Swap the pivot to its final location
        let tmp = arr[initialPivotLoc];
        arr[initialPivotLoc] = arr[finalPivotLoc];
        arr[finalPivotLoc] = tmp;

        return finalPivotLoc;
    }

    /**
     * Finds the (k+1)-th smallest element in the array using the "partition" function.
     * @param  {Array}  arr   The array which we operate on. We consider only the fragment in the interval [left, right)
     * @param  {Number} left  The index of the lower bound (INCLUSIVE) of the array fragment we operate on
     * @param  {Number} right The index of the upper bound (NON-INCLUSIVE) of the array fragment we operate on
     * @param  {Number} k     The index of the element that we seek if the array were sorted, k = 0, 1, 2, ...
     */
    static quickSelect(arr, left, right, k) {
        console.log(left + " " + right + " (k: " + k + ")"); // DEBUG
        if (k < left || k >= right) return -1; // Impossible to find element of index k in this range

        // Do a partition and save the resulting index.
        // The resulting pivot index will have the exact same position
        // it would have if the array were sorted
        let pivotIndex = Solution.partition(arr, left, right);
        console.log("--res: " + arr + " --> PI: " + pivotIndex); // DEBUG

        if (pivotIndex == k) return arr[k];
        else if (pivotIndex < k)
            return Solution.quickSelect(arr, pivotIndex + 1, right, k);
        // Search right
        else return Solution.quickSelect(arr, left, pivotIndex, k); // Search left
    }

    getSecondLargest(arr) {
        if (arr.length < 2) {
            return -1;
        }
        return Solution.quickSelect(arr, 0, arr.length, arr.length - 2);
    }
}
