package leetcode

import "slices"

func removeDuplicates(nums []int) int {
	// Offset is basically the number of elements we have deleted.
	// The name comes from the fact that when we'll be iterating
	// through `nums`, the current element will be `nums[i - offset]`.
	// This way we'll not skip any elemens due to deletion when the
	// index `i` will not adapt to disappearing elements.
	offset := 0

	// The currently processed unique element.
	// We will remove any elements equal to it.
	currUnique := nums[0]

	n := len(nums)

	for i := 1; i < n; i++ {
		// fmt.Printf("currEl: %d\tcurrUn: %d", nums[i-offset], currUnique)

		if curr := i - offset; nums[curr] == currUnique {
			// Duplicate detected!
			// fmt.Print(" (X)")
			slices.Delete(nums, curr, curr+1)
			offset++
		} else {
			currUnique = nums[curr]
		}

		// fmt.Print("\n")
	}

	return n - offset
}
