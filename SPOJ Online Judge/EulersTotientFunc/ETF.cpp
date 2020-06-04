#include <cstdio>
#define MX 1000006
using namespace std;

int phi[MX];
static int increments[8] = {4, 2, 4, 2, 4, 6, 2, 6};

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


    int t, n;
    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        printf("%d\n", phi[n]);
    }

}