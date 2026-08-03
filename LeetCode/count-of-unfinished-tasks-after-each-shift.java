// https://leetcode.com/problems/count-of-unfinished-tasks-after-each-shift

class Solution {
    public int[] countTasks(int[] tasks, int[] shifts) {
        int n = tasks.length;
        int m = shifts.length;
        long[] sum = new long[n+1];
        for (int i = 1; i <= n; i ++) {
            sum[i] = sum[i-1] + tasks[i-1];
        }
        int[] ans = new int[m];
        int p = 0;
        long rem = 0;
        long u;
        for (int i = 0; i < m; i ++) {
            u = shifts[i];
            if (rem > u) {
                rem -= u;
                ans[i] = n - p;
            } else {
                if (rem > 0) {
                    u -= rem;
                    rem = 0;
                    p = (p + 1) % n;  
                    if (p == 0) {
                        ans[i] = 0;
                        continue;
                    }
                } 
                // rem == 0 
                if (tasks[p] > u) {
                    rem = tasks[p] - u;
                    ans[i] = n - p;
                } else {
                    // lo, hi are 1-indexed and inclusive []
                    // new_p is 1-indexed
                    int lo = p+1, hi = n, new_p = p+1;
                    while (lo <= hi) {
                        int mid = (lo + hi) / 2;
                        long csum = sum[mid] - sum[p];
                        if (csum > u) {
                            hi = mid - 1;
                        } else {
                            lo = mid + 1;
                            new_p = mid;
                        }
                    }
                    if (new_p == n) {
                        ans[i] = 0;
                    } else {
                        rem = sum[new_p] - sum[p] - u;
                        if (rem < 0) {
                            rem += tasks[new_p];
                        }
                        ans[i] = n - new_p;
                    }
                    p = new_p % n;
                }
            }
        }
        return ans;
    }
}
