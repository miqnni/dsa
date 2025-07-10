// Solution notes: ../../notes/boolean_parenthesisation.png

class Solution {
    /**
     * A NOT function for a number representing exactly one bit. The function turns:
     * - 0 into 1
     * - 1 into 0
     * @param {number} a The number whose value is either 0 or 1
     * @returns {number} The negation of a
     */
    not1b(a) {
        return a ^ 1;
    }

    /**
     * A recursive function with memoisation that counts the number of ways
     * we can parenthesise the fragment [l, r) of expression expr
     * in order to obtain the boolean result res.
     * @param   {string} expr The expression consisting of alternating T/F symbols and &/|/^ operators that is meant to be parenthesised
     * @param   {number} l    The lower bound of the considered fragment of expression. Inclusive
     * @param   {number} r    The upper bound of the considered fregment of expression. Non-inclusive
     * @param   {number} res  The expected result of the expression. 0 represents F, 1 represents T
     * @returns {number}      The number of ways we can parenthesise expr[l:r] to obtain the result res
     */
    f(expr, l, r, res) {
        // Error handling
        if (l % 2 === 1)
            throw new Error(
                "The lower bound of the expression must have an even value"
            );
        if (r % 2 === 0)
            throw new Error(
                "The upper bound of the expression must have an odd value"
            );
        if (l < 0)
            throw new Error(
                "The lower bound of the expression must have a positive value"
            );
        if (r > this.n)
            throw new Error(
                "The upper bound of the expression cannot exceed the length of the starting expression"
            );
        if (r <= l)
            throw new Error(
                "The upper bound of the expression must greater than its lower bound"
            );

        // Duplicate subproblems elimination
        if (this.dp[l][r][res] != -1) return this.dp[l][r][res];

        // Base case
        if (l === r - 1) {
            return expr[l] === "T" ? res : this.not1b(res);
        }

        // Recursion with memoisation
        let sumOfWays = 0;

        for (let i = l + 1; i < r; i += 2) {
            const leftTrue = this.f(expr, l, i, 1);
            const leftFalse = this.f(expr, l, i, 0);
            const rightTrue = this.f(expr, i + 1, r, 1);
            const rightFalse = this.f(expr, i + 1, r, 0);

            if (res === 1) {
                switch (expr[i]) {
                    case "&":
                        sumOfWays += leftTrue * rightTrue;
                        break;
                    case "|":
                        sumOfWays += leftTrue * rightTrue;
                    case "^":
                        sumOfWays += leftTrue * rightFalse;
                        sumOfWays += leftFalse * rightTrue;
                        break;
                    default:
                        throw new Error(
                            "An incorrect operator symbol in the expression has been found"
                        );
                }
            } else {
                switch (expr[i]) {
                    case "&":
                        sumOfWays += leftTrue * rightFalse;
                        sumOfWays += leftFalse * rightTrue;
                    case "|":
                        sumOfWays += leftFalse * rightFalse;
                        break;
                    case "^":
                        sumOfWays += leftFalse * rightFalse;
                        sumOfWays += leftTrue * rightTrue;
                        break;
                    default:
                        throw new Error(
                            "An incorrect operator symbol in the expression has been found"
                        );
                }
            }
        }

        this.dp[l][r][res] = sumOfWays;
        return sumOfWays;
    }

    /**
     * A driver function for the recursive function f that prepares the DP memoisation array and
     * makes the initial call of the function f.
     * @param {string} s The expression meant to be parenthesised
     */
    countWays(s) {
        // code here
        this.n = s.length;
        this.dp = Array.from({ length: this.n + 1 }, () =>
            Array.from({ length: this.n + 1 }, () => [-1, -1])
        );

        this.finalRes = -1;
        try {
            if (this.n % 2 === 0)
                throw new Error("The expression must have an odd length");
            if (
                ![...s].every((symbol, idx) => {
                    if (idx % 2 === 0) return symbol === "T" || symbol === "F";
                    return symbol === "&" || symbol === "|" || symbol === "^";
                })
            )
                throw new Error(
                    "The expression must consist of alternating T/F symbols and &/|/^ operators"
                );

            this.finalRes = this.f(s, 0, this.n, 1);
        } catch (e) {
            console.error(e);
            return -1;
        }
        return this.finalRes;
    }
}
