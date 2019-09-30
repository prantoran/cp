// https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050edc/000000000018666c

#include <bits/stdc++.h>
#define MX 128
#define INF 10000000
using namespace std;

int t, ca, n, k, a[MX];
int b[MX], bptr;
int id[2222];

int dp[MX][MX][MX], dn[MX][MX][MX];

int solve(int pos, int lastID, int diffCnt) {
    if (pos == n) {
        if (diffCnt > k) return INF;
        return 0;
    }
    
    if (dn[pos][lastID][diffCnt] == ca) {
        return dp[pos][lastID][diffCnt];
    }
    
    dn[pos][lastID][diffCnt] = ca;
    
    int ret = INF;
    int u = a[pos];
    int uID = id[u];
    
    for (int i = 0; i < bptr; i ++) {
        int cur = (i == uID) ? 0: 1;
        int curDiff = (pos == 0 || i == lastID)? 0: 1;
        cur = cur + solve(pos+1, i, diffCnt + curDiff);
        ret = min (ret, cur);
    }
    
    return dp[pos][lastID][diffCnt] = ret;
}

int main() {
    // freopen("data.in", "r", stdin);
    scanf("%d", &t);
    for (ca = 1; ca <= t; ca ++) {
        scanf ("%d %d", &n, &k);
        for (int i = 0; i < n; i ++) {
            scanf ("%d", &a[i]);
            b[i] = a[i];
        }
        
        sort(b, b+n);
        bptr = 0;
        for (int i = 0; i < n; i ++) {
            if (b[bptr] == b[i]) continue;
            bptr++;
            b[bptr] = b[i];
        }
        bptr++;
            
        for (int i = 0; i <bptr; i ++) {
            id[b[i]] = i;
        }
        
        printf("Case #%d: %d\n",ca, solve(0, id[a[0]], 0));
    }
    
    return 0;
}
