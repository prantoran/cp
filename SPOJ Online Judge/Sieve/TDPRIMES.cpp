#include <iostream>
#include <algorithm>
#include <vector>
#define LL long long
#define MOD 100
#define MX 100000000
using namespace std;


bool sieve[MX];

vector<int> primes;


int main() {

    sieve[0] = sieve[1] = 1;
    for (int i = 4; i < MX; i += 2) sieve[i] = 1;
    for (int i = 3; i*i < MX; i += 2) {
        if (!sieve[i]) {
            for (int j = i*i; j < MX; j += 2*i) sieve[j] = 1;
        }
    }

    primes.push_back(2);
    for (int i = 3; i < MX; i += 2) if (!sieve[i]) primes.push_back(i);
    for (int i = 0, n = primes.size(); i < n; i += 100) {
        printf("%d\n", primes[i]);
        
    }
    
    return 0;
}