#include <cstdio>

#define MX 2000006
#define LL long long
using namespace std;

int phi[MX];
static int increments[8] = {4, 2, 4, 2, 4, 6, 2, 6};

int depth[MX];
LL sum[MX];


int main() {

    phi[0] = 0;
    phi[1] = 1;

    for (int i = 2; i < MX; i ++) phi[i] = i;

    for (int i = 2; i < MX; i += 2) phi[i] -= phi[i]/2;
    for (int i = 3; i < MX; i += 3) phi[i] -= phi[i]/3;
    for (int i = 5; i < MX; i += 5) phi[i] -= phi[i]/5;

    // wheel factorization
    for (LL i = 0, p = 7; p < MX; p += increments[i++]) {
        if (phi[p] == p) 
            for (LL j = p; j < MX; j += p) phi[j] -= phi[j]/p;
        
        if (i == 8) i = 0;
    }

    depth[0] = depth[1] = 0;

    for (int i = 2; i < MX; i ++) depth[i] = depth[phi[i]] + 1;

    sum[0] = sum[1] = 0;

    for (int i = 2; i < MX; i ++) sum[i] = sum[i-1] + depth[i];

    int N, n, m;
    scanf ("%d", &N);
    while (N--) {
        scanf ("%d %d", &m, &n);

        printf("%lld\n", sum[n]-sum[m-1]);
    }

    return 0;
}