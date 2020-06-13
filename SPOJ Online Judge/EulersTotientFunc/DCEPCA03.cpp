
#include <cstdio>
#include <iostream>
#define MX 5000006

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

using u64 = unsigned long long;

int nextPrime[MX];
u64 phi[MX];

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
        phi[i] += phi[i-1];
    }

    for (int i = 1; i < MX; i ++) {
        phi[i] *= phi[i];
    }

    int t, n;
    scanf ("%d", &t);
    while (t--) {
        scanf("%d", &n);
     
        printf("%llu\n", phi[n]);
    }


    return EXIT_SUCCESS;
}