#include <bits/stdc++.h>
#define MX 600000
using namespace std;

const long long INF = 1 << 30;

int t, ca, n;
vector<long long> beauty;

vector< vector<int> > G;

int dn[MX][2][2];
long long dp[MX][2][2];

long long maxBeauty(int node, int parent, int parentColored, int selfColored) {

    if (dn[node][parentColored][selfColored] == ca) 
        return dp[node][parentColored][selfColored];
    
    dn[node][parentColored][selfColored] = ca;

    long long ret = 0;

    if (selfColored) {
        for (auto u: G[node]) {
            if (u == parent) continue;

            ret += max(maxBeauty(u, node, 1, 0), maxBeauty(u, node, 1, 1));
        }    

        ret += beauty[node];
    
    } else {
        if (parentColored) {
            for (auto u: G[node]) {
                if (u == parent) continue;

                ret += max(maxBeauty(u, node, 0, 0), maxBeauty(u, node, 0, 1));
            }

            ret += beauty[node];

        } else {
            // performing dp

            long long lightedNot; // not placed a lighthouse in any of the previous subtrees
            long long lighted; // placed a lighthouse in atleast one of the previous subtrees

            int childrenCnt = 0;

            for (auto u: G[node]) {
                if (u == parent) continue;

                long long maxBeautyULightedNot = maxBeauty(u, node, 0, 0);
                long long maxBeautyULighted = maxBeauty(u, node, 0, 1);

                if (childrenCnt == 0) {
                    lightedNot = maxBeautyULightedNot;
                    lighted = maxBeautyULighted;
                } else {

                    long long newLightedNot = lightedNot + maxBeautyULightedNot;
                    
                    long long newLighted = max(
                        lighted + max(maxBeautyULightedNot, maxBeautyULighted),
                        lightedNot + maxBeautyULighted
                    );

                    lightedNot = newLightedNot;
                    lighted = newLighted;
                }

                childrenCnt ++;
            }

            if (childrenCnt != 0) 
                ret = max(beauty[node] + lighted, lightedNot);
            else 
                ret = 0;
        }
    }

    return dp[node][parentColored][selfColored] = ret;
}

long long solve() {
    long long ret = 0;
    ret = max (maxBeauty(1, 0, 0, 0), maxBeauty(1, 0, 0, 1));

    return ret;
}

int main() {
    // freopen("data.in", "r", stdin);

    scanf("%d", &t);

    for (ca = 1; ca <= t; ca ++) {

        scanf("%d", &n);
    
        beauty = vector<long long> (n+1);
        for (int i = 1; i <= n; i ++) {
            scanf ("%lld", &beauty[i]);
        }

        G = vector<vector<int> > (n+1);
    
        for (int i = 1, u, v; i < n; i ++) {
            scanf ("%d %d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }

        printf("Case #%d: %lld\n", ca, solve());
    }
    
    return 0;
}
