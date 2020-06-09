// https://codeforces.com/gym/100975
#include <iostream>
#include <cmath>

using namespace std;

using u64 = long long;

u64 binpow(u64 a, u64 b, u64 m = (u64)1e18) {
    a %= m;
    u64 res = 1;
    while (b > 0) {
        if (b & 1) 
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }

    return res;
}

u64 phi(u64 n) {
    u64 result = n;
    for (u64 i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int main() {

    freopen("calc.in", "r", stdin);
    freopen("calc.out", "w", stdout);
    u64 n, k;

    // scanf ("%lld %lld", &n, &k);
    cin >> n >> k;

    u64 logm = 1+log2(k);
    u64 log2m = 1+log2(logm);

    u64 ans = 0, exponent;

    if (n >= log2m) {
        int phi_k = phi(k);
        exponent = binpow(2, n, phi_k);
        exponent += phi_k;
    } else {
        exponent = binpow(2, n);
    }

    ans = (1+binpow(2, exponent, k))%k;


    cout << ans;

    return 0;
}