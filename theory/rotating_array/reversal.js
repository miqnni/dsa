class Solution {
    /**
     * Function to reverse the part of the array between the left bound and the right bound.
     * Source: GeeksForGeeks / Rotate an Array by d - Counterclockwise or Left (GFG160)
     * @param {number[]} arr   The array to be modified.
     * @param {number}   left  The lower bound (INCLUSIVE)
     * @param {number}   right The upper bound (NON-INCLUSIVE)
     */
    static reverse(arr, left, right) {
        const n = arr.length;
        if (left < 0) throw "The lower bound cannot be smaller than 0";
        if (right > n)
            throw "The upper bound must be smaller than the array size";
        if (left >= right)
            throw "The lower bound must have a smaller value than the upper bound";

        for (let i = left; i < left + Math.floor((right - left) / 2); i++) {
            // console.log(i + " <-> " + (right - 1 - i));
            [arr[i], arr[left + (right - 1 - i)]] = [
                arr[left + (right - 1 - i)],
                arr[i],
            ];
        }
    }

    /**
     * Function to rotate an array by d elements in counter-clockwise direction using
     * REVERSAL ALGORITHM based on the observation that if we rotate the array by d positions,
     * the last (n - d) elements will be at the front
     * and the first d elements will be at the back.
     * Source: GeeksForGeeks / Rotate an Array by d - Counterclockwise or Left (GFG160)
     * @param {number[]} arr The array to be modified.
     * @param {number}   d   The number of positions that we rotate the array by (to the left).
     */
    rotateArr(arr, d) {
        const n = arr.length;
        if (n === 0) return;

        d %= n;
        if (d == 0) return;

        // STEP 1
        // Reverse the first d elements
        // E.g. [1, 2, 3, 4, 5, 6] -> [2, 1 | 3, 4, 5, 6] (d = 2 | n - d = 4)
        Solution.reverse(arr, 0, d);
        // console.log(arr);

        // STEP 2
        // Reverse the last n-d elements (i.e. remaining elements)
        // E.g. [2, 1 | 3, 4, 5, 6] -> [2, 1 | 6, 5, 4, 3]
        Solution.reverse(arr, d, n);
        // console.log(arr);

        // STEP 3
        // Reverse the entire array
        // E.g. [2, 1 | 6, 5, 4, 3] -> [3, 4, 5, 6, 1, 2]
        Solution.reverse(arr, 0, n);
        // console.log(arr);
    }
}
