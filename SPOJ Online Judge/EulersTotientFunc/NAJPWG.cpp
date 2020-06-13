
#include <cstdio>
#define MX 100005

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

int nextPrime[MX];
int phi[MX];

int main() {

    phi[0] = 0;
    phi[1] = 1;

    for (int p, i = 2; i < MX; i ++) {
        p = nextPrime[i];
        if (p) {
            if ((i/p)%p)
                phi[i] = phi[i/p]*(p-1);
            else
                phi[i] = phi[i/p]*p;
        } else {
            phi[i] = i-1;
            for (int j = i; j < MX; j += i) {
                nextPrime[j] = i;
            }
        }
    }

    for (int i = 1; i < MX; i ++) {
        phi[i] = i-phi[i];
    }


    for (int i = 1; i < MX; i ++) {
        phi[i] += phi[i-1];
    }

    int t, n;
    scanf ("%d", &t);
    for (int ca = 1; ca <= t; ca ++) {
        scanf("%d", &n);
     
        printf("Case %d: %d\n", ca, phi[n]);
    }


    return 0;
}