
#include <cstdio>
#define MOD 1000000007
#define MX 10000007

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
int F[MX];
int primeSum[MX];
long long fact[MX];

inline long long binpow(long long a, long long b, long long m) {
    a %= m;
    
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }

    return res;
}


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
            primeSum[i] ++;
            phi[i] = i-1;
            for (int j = i; j < MX; j += i) {
                nextPrime[j] = i;
            }
        }
    }

    for (int i = 1; i < MX; i ++) {
        primeSum[i] += primeSum[i-1];
    }

    for (int i = 0; i < MX; i ++) {
        F[i] = primeSum[i] - phi[i];
        if (F[i] < 0) F[i] = 0;
    }

    fact[0] = 1;
    for (int i = 1; i < MX; i ++) {
        fact[i] = (fact[i-1]*i) % (MOD-1);
    }


    int t, n;
    scanf ("%d", &t);
    while (t--) {
        scanf("%d", &n);
     
        printf("%lld\n", binpow(phi[n], fact[F[n]], MOD));
    }


    return 0;
}