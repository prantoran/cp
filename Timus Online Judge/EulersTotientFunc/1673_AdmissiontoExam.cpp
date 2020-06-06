#include <cstdio>
#include <initializer_list>
#include <bitset>
#include <math.h>
#include <iostream>
#include <map>
#include <algorithm>

#define MX 2000006
#define LL long long
using namespace std;


LL binpower(LL base, LL e, LL mod) {
    LL result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = result * base % mod;
        base = base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(LL n, LL a, LL d, int s) {
    LL x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool isPrimeMillerRabin(LL n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    LL d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

bitset<MX> sieve;
static int increments[8] = {4, 2, 4, 2, 4, 6, 2, 6};
int primes[MX], pdx;

bool isPrime(LL p) {
    if (p < MX) return sieve[p] == 0;
    return isPrimeMillerRabin(p);
}

map<pair<LL, LL>, LL> dp;
map<pair<LL, LL>, bool> dn;

LL divisors[MX], divIdx;

LL solve(LL n, LL startID = 0) {
    
    if (dn[{n, startID}]) {
        return dp[{n, startID}];
    }
    dn[{n, startID}] = 1;

    LL ans = 0;

    bool entered = false;

    for (LL i = startID, divisor, p, cur, u, prefix; i < divIdx; i ++) {
        
        divisor = divisors[i];
        if (divisor > n) {
            break;
        }

        if (n%divisor) continue;

        p = divisor+1;
        if (isPrime(p)) {
            
            prefix = p;
            u = n/divisor;

            while(true) {
                if (u != n) {
                    cur = prefix * solve(u, i+1);

                    if (cur && (!ans || ans > cur)) {
                        entered = true;
                        ans = cur; 
                    }
                }

                if (u%p) break;
                prefix *= p;
                u /= p;
            }
        }
    }
    
    if (!entered) {
        if (n == 1) {
            ans = 1;
        }
    }

    return dp[{n, startID}] = ans;
}

int main() {

    sieve[0] = 1;
    sieve[1] = 1;

    for (int i = 4; i < MX; i += 2) sieve[i] = 1;
    for (int i = 6; i < MX; i += 3) sieve[i] = 1;
    for (int i = 10; i < MX; i += 5) sieve[i] = 1;

    // wheel factorization
    for (LL i = 0, p = 7; p*p < MX; p += increments[i++]) {
        if (!sieve[p]) 
            for (LL j = p*p; j < MX; j += 2*p) sieve[j] = 1;
        
        if (i == 8) i = 0;
    }

    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    
    for (int i = 0, p = 7; p < MX; p += increments[i++]) {
        if (!sieve[p]) primes[pdx++] = p;
        
        if (i == 8) i = 0;
    }

    dn.clear();

    LL n;
    scanf ("%lld", &n);

    divIdx = 0;
    for (LL i = 1; i*i <= n; i ++) {
        if (!(n%i)) {
            divisors[divIdx++] = i;
            if (i*i < n) divisors[divIdx++] = n/i;
        }
    }
    
    sort(divisors, divisors + divIdx);

    printf("%lld\n", solve(n));

}