#include <cstdio>
#include <bitset>
#define MX 100006
using namespace std;

bitset<MX> sieve;
static int increments[8] = {4, 2, 4, 2, 4, 6, 2, 6};
int primes[MX], pdx;

int main() {

    


    for (int i = 4; i < MX; i += 2) sieve[i] = 1;
    for (int i = 3; i < MX; i += 3) sieve[i] = 1;
    for (int i = 5; i < MX; i += 5) sieve[i] = 1;

    // wheel factorization
    for (int i = 0, p = 7; p*p < MX; p += increments[i++]) {
        if (!sieve[p]) 
            for (int j = p*p; j < MX; j += 2*p) sieve[j] = 1;;
        
        if (i == 8) i = 0;
    }

    primes[0] = 2; primes[1] = 3; primes[2] = 5;
    pdx = 3;
    for (int i = 0, p = 7; p < MX; p += increments[i++]) {
        if (!sieve[p]) primes[pdx++] = p;

        if (i == 8) i = 0;
    }


    int n, phi;
    
    while (true) {
        scanf ("%d", &n);
        if (!n) break;

        phi = n;

        for (int i = 0, p; i < pdx; i++) {
            
            p = primes[i];
            if (p > n) break;

            if (!(n%p)) {
                while (!(n%p)) n/=p;
                phi -= phi/p;
            }
        } 

        if (n > 1) phi -= phi/n;

        printf("%d\n", phi);
    }

}