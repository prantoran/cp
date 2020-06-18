
#include <cstdio>
#include <iostream>
#define MX 1000006
#define MOD 1000000007
using namespace std;

#if DEBUG == 2
    #include <iostream>
    #define LOG(x) cerr << #x <<":" << x << "\n"
#elif defined(DEBUG)
    #include <iostream>
    #define LOG(x) cerr << "concise:" << x << "\n";
#else
    #define LOG(x)
#endif

using u64 = long long;

u64 inv[MX];
u64 fact[MX];
u64 invfact[MX];

int a[1004];

u64 ncr(int n, int r) {
    return (fact[n]*invfact[r]%MOD)*invfact[n-r]%MOD;
}

int main() {

    inv[1] = 1;
    for (int i = 2; i < MX; i ++) {
        inv[i] = (MOD - (MOD/i)*inv[MOD%i]%MOD) % MOD;
    }


    fact[0] = 1, fact[1] = 1;
    invfact[1] = 1;
    invfact[0] = 1;
    for (int i = 2; i < MX; i ++) {
        fact[i] = fact[i-1]*i % MOD;
        invfact[i] = invfact[i-1]*inv[i] % MOD;
    }


    int t, n;
    u64 ans, sum;

    scanf ("%d", &t);

    for (int ca = 1; ca <= t; ca ++) {
        scanf ("%d", &n);
        for (int i = 0; i < n; i ++) {
            scanf("%d", &a[i]);
        }

        ans = 1, sum = a[0];
        for (int i = 1, r; i < n; i ++) {
            r = a[i]-1;
            sum += a[i];
            ans = ans*ncr(sum-1, r) % MOD;
        }

        printf("Case %d: %lld\n", ca, ans);
    }


    return EXIT_SUCCESS;
}