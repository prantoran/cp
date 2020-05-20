#include <iostream>
#define LL long long
#define MOD 1000000007
using namespace std;

pair<LL, LL> fib (LL n) {
    if (n == 0)
        return {0, 1};

    auto p = fib(n >> 1);
    LL c = (p.first * ((2 * p.second)%MOD - p.first + MOD)) % MOD;
    LL d = ( (p.first * p.first)%MOD + (p.second * p.second)%MOD + MOD) % MOD;
    if (n & 1)
        return {d, (c + d + MOD)%MOD};
    else
        return {c, d};
}

int main() {

    int t;
    LL N;
    pair<LL, LL> ans;

    scanf ("%d", &t);
    for (int ca = 1; ca <= t; ca ++) {
        scanf("%lld", &N);
        if (N == 1) {
            printf("2\n");
            continue;
        } else if (N == 0) {
            printf("0\n");
            continue;
        } else {
            ans = fib(N+1);
        }
        // cout << ans.first << " " << ans.second << " n:" << N << endl;
        printf("%lld\n", (ans.first + ans.second + MOD)%MOD);
        // printf("%lld\n", (ans.first)%MOD);

    }
    
    return 0;
}