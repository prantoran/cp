#include <iostream>
#include <algorithm>
#include <vector>
#define LL long long
#define MX 10000007
using namespace std;


bool sieve[MX];

vector<int> primes;
vector<int> p2, p4;

int sum[MX];

int main() {

    sieve[0] = sieve[1] = 1;
    for (int i = 4; i < MX; i += 2) sieve[i] = 1;
    for (int i = 3; i*i < MX; i += 2) {
        if (!sieve[i]) {
            for (int j = i*i; j < MX; j += 2*i) sieve[j] = 1;
        }
    }

    for (int i = 1; i*i < MX; i ++) p2.push_back(i*i);
    for (int i = 1; i*i*i*i < MX; i ++) p4.push_back(i*i*i*i);

    for (auto x: p2) 
        for (auto y: p4) 
            if (x+y < MX && !sieve[x+y]) sum[x+y] = 1;

    for (int i = 1; i < MX; i ++) sum[i] += sum[i-1];

    int t, n;
    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        printf ("%d\n", sum[n]);
    }    

    
    return 0;
}