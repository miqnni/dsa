// 1137. N-th Tribonacci Number
package leetcode

func tribonacci(n int) int {
	if n < 1 {
		return 0
	}
	if n < 3 {
		return 1
	}

	tab := make([]int, n+1, n+1)
	tab[1], tab[2] = 1, 1

	for i := 3; i < n+1; i++ {
		tab[i] = tab[i-1] + tab[i-2] + tab[i-3]
	}
	return tab[n]
}
