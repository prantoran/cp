#include <cstdio>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>
#define LL long long
#define MX 105000105
using namespace std;



bitset<MX> sieve;
int primes[MX], pdx;

int tot[MX], sum1[MX];

int main() {

    for (int i = 4; i < MX; i += 2) sieve[i] = 1;
    for (int i = 3; i*i < MX; i += 2) {
        if (!sieve[i]) {
            for (int j = i*i; j < MX; j += 2*i) sieve[j] = 1;
        }
    }

    primes[0] = 2;
    pdx = 1;
    for (int i = 3; i < MX; i += 2) if (!sieve[i]) primes[pdx++] = i;


    for (int i = 0, ones, zeros, p; i < pdx; i ++) {
        ones = 0;
        zeros = 0;
        p = primes[i];
        while (p) {
            ones += p%2;
            zeros += !(p%2);
            p /= 2;
        }

        tot[i] = ones + zeros;
        sum1[i] = ones;
    }

    for (int i = 1; i < pdx; i ++) {
        tot[i] += tot[i-1];
        sum1[i] += sum1[i-1];
    }
    
    int t, N, ans, p, n;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &N);

        int lo = 0, hi = pdx-1;
        int id = -1;
        while (lo <= hi) {
            int mid = (lo+hi)/2;
            if (tot[mid] <= N) {
                    id = mid;
                    lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        N -= tot[id];
        ans = sum1[id];
        if (N) {
            p = primes[id+1];
            n = tot[id+1]-tot[id];

            for (int i = n-N; i < n; i ++) {
                if (p & (1<<i)) ans ++;
            }
        }

        printf("%d\n", ans);
    }
}
