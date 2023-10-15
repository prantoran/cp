// https://leetcode.com/problems/regular-expression-matching

class Solution {
    int n, m;
    map<pair<int, int>, bool> dp;
    map<pair<int, int>, bool> dn;

    bool dfs(const string & s, const string & p, int i = 0, int j = 0) {

        if (j == m) return (i == n);
        if (i == n) {
            while (j < m) {
                if (p[j] == '*' || p[j+1] != '*') return false;
                j += 2;
            }

            return j == m;
        }
        
        if (dn[{i, j}]) return dp[{i, j}];
        dn[{i, j}] = true;

        bool ans = false;
            
        if (p[j] == '.') {
            if (j+1 < m && p[j+1] == '*') {
                for (int k = i; k <= n; k ++) {
                    if (dfs(s, p, k, j+2)) {
                        ans |= true;
                        break;
                    }
                }
            } else {
                ans |= dfs(s, p, i+1, j+1);
            }
        } else if (s[i] == p[j]) {
            if (j+1 < m && p[j+1] == '*') {
                ans |= dfs(s, p, i, j+2);
                for (int k = i; k < n; k ++) {
                    if (s[k] != p[j]) break;
                    if (dfs(s, p, k+1, j+2)) {
                        ans |= true;
                        break;
                    }
                }
            } else {
                ans |= dfs(s, p, i+1, j+1);
            }
        }

        if (s[i] != p[j] && j+1 < m && p[j+1] == '*') {
            ans |= dfs(s, p, i, j+2);
        }
        
        return dp[{i, j}] = ans;
    }

public:
    bool isMatch(string s, string p) {
        n = s.length();
        m = p.length();
        dp = map<pair<int, int>, bool>();
        dn = map<pair<int, int>, bool>();
        return dfs(s, p);
    }
};
