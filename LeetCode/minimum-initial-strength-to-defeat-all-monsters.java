// https://leetcode.com/problems/minimum-initial-strength-to-defeat-all-monsters

class Solution {
    public long minInitialStrength(int[] monsters, int[][] boosts) {
        int n = monsters.length;
        int m = boosts.length;

        Arrays.sort(boosts, (u, v) -> {
            if (u[0] == v[0])
                return Integer.compare(u[1], v[1]);
            return Integer.compare(u[0], v[0]);
        });

        long curTot = 0;
        long[] totBoosts = new long[n+1];
        for (int i = 0 ; i < m; i ++) {
            totBoosts[boosts[i][0]] += boosts[i][2];
            totBoosts[boosts[i][1] + 1] -= boosts[i][2];
        }

        for (int i = 1; i < n; i ++) {
            totBoosts[i] += totBoosts[i-1];
        }

        long ans = 0;
        long lo = 0, hi = (long)1e17;
        while (lo <= hi) {
            long mid = (lo + hi) / 2;
            boolean possible = true;
            long cur = mid;
            for (int i = 0 ;possible && i < n; i ++) {
                if (cur + totBoosts[i] >= monsters[i]) {
                    cur -= monsters[i];
                    if (cur < 0) cur = 0;
                } else {
                    possible = false;
                }
            }
            if (possible) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
}
