
#include <cstdio>
#define MX 1000006

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

using u64 = long long;

int nextPrime[MX], phi[MX];
u64 gcdSum[MX];

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

        for (int j = i; j < MX; j += i) {
            gcdSum[j] += (u64)(j/i)*phi[i];
        }
    }
    
    for (int i = 1; i < MX; i ++)
        gcdSum[i] += gcdSum[i-1];

    int n;
    while (scanf("%d", &n)) {
        if (!n) break;
        printf("%lld\n", gcdSum[n]);
    }


    return 0;
}