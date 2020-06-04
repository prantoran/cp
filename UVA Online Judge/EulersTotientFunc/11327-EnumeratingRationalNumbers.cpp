#include <cstdio>

#define MX 200006
#define LL long long
using namespace std;

inline int gcd ( int a, int b ) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while ( b ) { 
        a = a % b; 
        a ^= b;
        b = a^b;
        a ^= b;
    } 
    return a;
}

int phi[MX];
static int increments[8] = {4, 2, 4, 2, 4, 6, 2, 6};
LL phisum[MX];

int main() {

    phi[0] = 0;
    phi[1] = 1;

    for (int i = 2; i < MX; i ++) phi[i] = i;

    for (int i = 2; i < MX; i += 2) phi[i] -= phi[i]/2;
    for (int i = 3; i < MX; i += 3) phi[i] -= phi[i]/3;
    for (int i = 5; i < MX; i += 5) phi[i] -= phi[i]/5;

    // wheel factorization
    for (int i = 0, p = 7; p < MX; p += increments[i++]) {
        if (phi[p] == p) 
            for (int j = p; j < MX; j += p) phi[j] -= phi[j]/p;
        
        if (i == 8) i = 0;
    }

    phisum[0] = 0;
    for (int i = 1; i < MX; i ++) phisum[i] = phisum[i-1] + phi[i];

    LL n;
    int lo, hi, d, k, num;
    while (true) {
        scanf ("%lld", &n);

        if (!n) break;

        if (n == 1) {
            printf("0/1\n");
            continue;
        } else if (n == 2) {
            printf("1/1\n");
            continue;
        }

        n --;

        lo = 0, hi = MX-1;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            if (phisum[mid] < n) {
                lo = mid + 1;
            } else {
                d = mid;
                hi = mid;
            }
        }

        k = n - phisum[d-1];

        for (int i = 1; k; i ++) {

            if (gcd(i, d) == 1) {
                k --;
                num = i;
            }
        }

        printf("%d/%d\n", num, d);
    }


}