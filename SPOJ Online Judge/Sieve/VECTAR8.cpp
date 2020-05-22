#include <iostream>
#include <algorithm>
#include <vector>
#define LL long long
#define MX 1000007
using namespace std;


bool sieve[MX];

vector<int> primes;
vector<int> p2, p4;

int sum[MX];

int main() {

    sieve[0] = sieve[1] = 1;
    for (int i = 4; i < MX; i += 2) sieve[i] = 1;
    for (int i = 3; i*i < MX; i += 2)
        if (!sieve[i]) 
            for (int j = i*i; j < MX; j += 2*i) sieve[j] = 1;
    

    sum[2] = 1;

    for (int i = 3,  ok;i < MX; i += 2) {
        if (sieve[i]) continue;
        ok = 1;

        for (int j = 10; ok && j < MX; j *= 10) {
            if (sieve[i%j]) ok = 0;
        }

        int k = i;
        while (k && ok) {
            if (!(k%10)) ok = 0;
            k /= 10;
        }

        if (ok) {
            sum[i] = 1;
        }
    }


    for (int i = 1; i < MX; i ++) sum[i] += sum[i-1];

    int t, n;
    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        printf ("%d\n", sum[n]);
    }

    return 0;
}