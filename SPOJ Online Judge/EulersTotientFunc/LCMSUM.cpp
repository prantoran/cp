
// https://forthright48.com/spoj-lcmsum-lcm-sum/
// https://www.quora.com/What-is-the-algorithm-behind-the-LCM-Sum-problem-on-SPOJ

#include <cstdio>
#include <bitset>

#define MX 1000006
using namespace std;

using u64 = uint64_t;
using u128 = __uint128_t;

int phi[MX], nextPrime[MX];
u64 ans[MX];

void preCalc() {
    phi[1] = 1;
    ans[1] = 1;

    for (int p, i = 2; i < MX; i ++) {

        if (nextPrime[i]) {
            p = nextPrime[i];
            // invariance: phi[x] calculated at this point 
            // for all x < i
            // Find phi(i) using phi(i/p)
            if ((i/p)%p) 
                phi[i] = phi[i/p]*(p-1);
            else
                phi[i] = phi[i/p]*p;
        } else {
            phi[i] = i-1;
            // Update prime factor for all multiples
            for (int j = i; j < MX; j += i)
                nextPrime[j] = i;
        }

        // invariance: phi[i] calculated at this point 

        // Update answer for all multiples
        for (int j = i; j < MX; j += i)
            ans[j] += (u64)i*phi[i];
        
        // special case: +2 for k = 1
        // multiply by n/2
        ans[i] = ((ans[i] + 2) * i) / 2;
    }
}

int main() {

    preCalc();
    
    int T, n;
    scanf ("%d", &T);
    while (T--) {
        scanf ("%d", &n);
        printf("%lu\n", ans[n]);
    }

    return 0;
}