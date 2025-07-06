class Solution {
    static gcd(a, b) {
        while (b !== 0) {
            const tmp = b;
            b = a % b;
            a = tmp;
        }
        return a;
    }

    static gcdRecursive(a, b) {
        if (a === 0) return b;
        return gcd(b % a, a);
    }

    /**
     * Function to rotate an array by d elements in counter-clockwise direction using
     * JUGGLING ALGORITHM FOR LEFT ROTATION
     * @param {number[]} arr The array to be modified.
     * @param {number}   d   The number of positions that we rotate the array by (to the left).
     */
    rotateArr(arr, d) {
        const n = arr.length;
        if (n === 0) return;

        d %= n;

        const cycles = Solution.gcd(d, n);

        // For each INDEPENDENT cycle
        for (let i = 0; i < cycles; i++) {
            const startEl = arr[i];
            let currIdx = i;
            let nextIdx = (currIdx + d) % n;

            while (nextIdx != i) {
                arr[currIdx] = arr[nextIdx];
                currIdx = nextIdx;
                nextIdx = (currIdx + d) % n;
            }

            arr[currIdx] = startEl;
        }
    }
}
