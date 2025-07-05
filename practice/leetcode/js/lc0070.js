// 70. Climbing Stairs

/**
 * @param {number} n
 * @return {number}
 */
var climbStairs = function (n, memo = {}) {
    if (n in memo) return memo[n];
    if (n < 2) return 1;
    memo[n] = climbStairs(n - 1, memo) + climbStairs(n - 2, memo);
    return memo[n];
};
