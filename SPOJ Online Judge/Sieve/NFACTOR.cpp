#include <cstdio>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>
#define LL long long
#define MX 1000105
using namespace std;



int sieve[MX];
int sum[20][MX];


int main() {

    for (int i = 2; i < MX; i += 2) sieve[i] = 1;
    for (int i = 3; i < MX; i += 2) {
        if (!sieve[i]) {
            for (int j = i; j < MX; j += i) sieve[j]++;
        }
    }

    for (int i = 1; i < MX; i ++) sum[sieve[i]][i] ++;
    for (int i = 0; i < 20; i ++)
        for (int j = 1; j < MX; j ++) sum[i][j] += sum[i][j-1];
    

    
    int t, a, b, n;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d %d %d", &a, &b, &n);
        printf("%d\n", sum[n][b]-sum[n][a-1]);
    }
}
