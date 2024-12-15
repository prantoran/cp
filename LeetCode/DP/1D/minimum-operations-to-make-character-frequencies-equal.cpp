// https://leetcode.com/problems/minimum-operations-to-make-character-frequencies-equal
class Solution {
public:
    int makeStringGood(string s) {
        vector<int> freq(26, 0);
        for (char c: s) {
            freq[c-'a'] ++;
        }
        int n = s.length();
        int ans = n;
        for (int u: freq) {
            ans = min(ans, n - u);
        }

        for (int k = 1; k <= n; k ++) {
            vector<int> dp(26, -1);
            ans = min(ans, dfs(dp, freq, k, 0));
        }

        return ans;
    }

    int dfs(vector<int> & dp, const vector<int> & freq, const int k, const int i) {
        if (i >= 26) {
            return 0;
        }

        if (dp[i] != -1) {
            return dp[i];
        }

        int ans = INT_MAX;
        if (freq[i] >= k) {
            int diff = freq[i] - k;
            ans = diff + dfs(dp, freq, k, i+1);
            if (i+1 < 26 && freq[i+1] <= k) {
                if (freq[i+1] + diff < k) {
                    diff = min(diff + (k - (freq[i+1] + diff)), diff + freq[i+1]);  
                }
                ans = min(ans, diff + dfs(dp, freq, k, i+2));
            }
        } else {
            int diff = k - freq[i];
            ans = min(freq[i], diff) + dfs(dp, freq, k, i + 1);
            if (i+1 < 26 && freq[i+1] <= k) {
                if (freq[i+1] + freq[i] >= k) {
                    diff = freq[i];
                } else {
                    diff = freq[i] + (k - (freq[i] + freq[i+1]));
                }
                ans = min(ans, diff + dfs(dp, freq, k, i+2));
            }
        }

        return dp[i] = ans;
    }
};
