#include <cstdio>
#include <bitset>

#define MX 2000006
using namespace std;

using u64 = uint64_t;
using u128 = __uint128_t;

bitset<MX> sieve;
static int increments[8] = {4, 2, 4, 2, 4, 6, 2, 6};

int primes[MX], pdx;
int dishes[MX];
int sum[MX];

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == (n-1)) 
        return false;
    for (int r = 1; r < s; r ++) {
        x = (u128)x * x % n;
        if (x == (n-1))
            return false;
    }
    return true;
}

bool MillerRabin(u64 n) {
    if (n < MX) return !sieve[n];

    int r = 0;
    u64 d = n - 1;
    while ((d&1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a: {2, 3, 5, 7, 11, 13, 17, 23, 29, 31, 37}) {
        if (check_composite(n, a, d, r)) return false;
    }

    return true;
}



int main() {

    sieve[0] = 1;
    sieve[1] = 1;


    for (int i = 4; i < MX; i += 2) sieve[i] = 1;
    for (int i = 6; i < MX; i += 3) sieve[i] = 1;
    for (int i = 10; i < MX; i += 5) sieve[i] = 1;

    // wheel factorization
    for (u64 i = 0, p = 7; p*p < MX; p += increments[i++]) {
        if (!sieve[p]) 
            for (u64 j = p*p; j < MX; j += 2*p) sieve[j] = 1;
        
        if (i == 8) i = 0;
    }

    primes[0] = 2, primes[1] = 3, primes[2] = 5;
    for (u64 i = 0, p = 7; p < MX; p += increments[i++]) {
        if (!sieve[p]) primes[pdx++] = p;
        
        if (i == 8) i = 0;
    }

    int N, Q, l, r;
    scanf ("%d %d", &N, &Q);
    for (int i = 1; i <= N; i ++) scanf ("%d", &dishes[i]);
    
    for (int i = 1, u, phi; i <= N; i ++) {
        u = dishes[i];
        phi = u;

        for (int j = 0, p = 2;j < pdx && p*p <= u; p = primes[j], j++) {
            if (!(u%p)) {
                while (!(u%p)) u /= p;
                phi -= phi/p;
            }
        }

        if (u > 1) phi -= phi/u;

        if (MillerRabin(phi)) sum[i] = 1;
    }

    for (int i = 1; i <= N; i ++) sum[i] += sum[i-1];

    while (Q--) {
        scanf ("%d %d", &l, &r);
        printf("%d\n", sum[r] -sum[l-1]);
    }




    return 0;
}