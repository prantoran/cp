#include <bits/stdc++.h>
#define MX 60000
using namespace std;

int t, ca, s, n;

vector<int> a[MX];

unordered_map<string, int> subsets;

string conv(int u) {
    string ret = "";

    while (u) {
        ret += (char)('0' + u%10); 
        u/=10;
    }

    return ret;
}

int main() {
//   freopen("data.in", "r", stdin);
    scanf("%d", &t);
    for (ca = 1; ca <= t; ca ++) {
        scanf ("%d %d", &n, &s);
        
        subsets.clear();
        
        for (int i = 0, c; i <n; i ++ ) {
            scanf ("%d", &c);
            a[i].resize(c);
            for (int j = 0;j < c; j ++) {
                scanf("%d", &a[i][j]);
            }
            
            sort(a[i].begin(), a[i].end());
            
            string key = "";
            for (auto u: a[i]) {
                key += "-" + conv(u);
            }
            
            subsets[key] ++;
        }
        
        long long ans = 0;
        
        for (int i = 0; i < n; i ++) {
            int sz = a[i].size();
            int cnt = 0;
            
            for (int j = 0, len = (1<<sz); j < len; j ++) {
                string key = "";
                for (int k = 0; k < sz; k ++) {
                    if (j & (1<<k)) {
                        key += "-" + conv(a[i][k]);
                    }
                }
                
                cnt += subsets[key];
            }
            
            ans += (n - cnt);
        }
        
        printf("Case #%d: %lld\n", ca, ans);
    }
    
    return 0;
}
