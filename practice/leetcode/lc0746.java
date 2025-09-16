package leetcode;

import java.util.HashMap;
import java.util.Map;

class lc0746 {
    private int[] c;
    private Map<Integer, Integer> memo;

    private int f(int i) {
        if (i < 2)
            return 0;
        if (memo.containsKey(i))
            return memo.get(i);
        int res = Math.min(
                c[i - 2] + f(i - 2),
                c[i - 1] + f(i - 1));
        memo.put(i, res);
        return res;
    }

    public int minCostClimbingStairs(int[] cost) {
        this.c = cost;
        this.memo = new HashMap<>();

        return f(cost.length);
    }
}