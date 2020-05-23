#include <cstdio>
#include <algorithm>
#include <bitset>
#include <vector>
#define LL long long
#define MX 11000000
using namespace std;

bitset<MX> sieve;
LL primes[MX];
int pdx;
vector<LL> p2;

int main() {
    for (int i = 4; i < MX; i += 2) sieve[i] = 1;
   
    for (int i = 3; i*i < MX; i += 2) {
        if (sieve[i]) continue;
        for (int j = i*i; j < MX; j += 2*i) sieve[j] = 1;
    }

    primes[0] = 2;
    pdx = 1;

    for (int i = 3; i < MX; i += 2) if (!sieve[i]) primes[pdx++] = i;

    for (int i = 0; i < pdx; i ++)
        for (int j = i+1; j < pdx; j ++) {
            LL v = primes[i]*primes[j];
            if (v > MX) break;
            p2.push_back(v);
        }
    
    sort(p2.begin(), p2.end());

    int t;
    LL n;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        printf("%lld\n", p2[n-1]);
    }

    return 0;
}