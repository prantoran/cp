// https://leetcode.com/problems/longest-palindromic-substring
// AUTHOR: Pinku Deb Nath

int idx(int i, int j, int n) {
    return i*(n+1) + j;
}

char* longestPalindrome(char* s) {
    int n = strlen(s);
    bool * dp = (bool *)malloc((n+1)*(n+1)*sizeof(bool));
    int st = 0, mxlen = 1;
    for (int i = 0; i <= n; i ++) {
        dp[idx(0,i,n)] = true;
        dp[idx(1,i,n)] = true;
    }
    for (int len = 2; len <= n; len++) {
        for (int lft = 0; lft+len <= n; lft++) {
            dp[idx(len, lft, n)] = false;
            if (s[lft] != s[lft+len-1]) {
                continue;
            }
            if (dp[idx(len-2, lft+1, n)] == false) {
                continue;
            }
            dp[idx(len,lft,n)] = true;
            if (mxlen < len) {
                st = lft;
                mxlen = len;
            }
        }
    }
    char *ans = (char *)malloc((st+mxlen+1)*sizeof(char));
    strncpy(ans, s+st, mxlen);
    ans[mxlen] = 0;
    return ans;
}
