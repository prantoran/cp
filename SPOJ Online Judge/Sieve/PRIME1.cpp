#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <bitset>
using namespace std;
 
#define MX 200005
#define LL long long 
// #define MX 10
 
int lp[MX];
int pr[MX], pdx;
 
bitset<MX> sieveSeg;
int primesSeg[MX], pdxs;
 
void solve(LL m, LL n) {
    pdxs = 0;
    sieveSeg.reset();
    LL p;
        
    for (int i = 0; i < pdx; i ++) {
        p = pr[i];
        for (LL j = max(p, (m+p-1)/p)*p; j <= n; j += p) {
            sieveSeg[j-m] = 1;
             
        }
    }
    
    if (m == 1) sieveSeg[0] = 1;
    
    for (LL j = m; j <= n; j ++) {
        if (!sieveSeg[j-m]) {
            printf("%lld\n", j);
        }
    }
    
    
}
 
int main()
{
	pdx = 0;
    for (int i = 2, lpi; i < MX; i ++) {
        if (!lp[i]) {
            lp[i] = i;
            pr[pdx++] = i;
          
        }
        
        lpi = lp[i];
        
        for (int j = 0, u; j < pdx && pr[j] <= lpi && i*pr[j] < MX; j ++) {
            u = i*pr[j];
            lp[u] = pr[j];
            
        }
        
    }

    LL m, n;
    int t;
    scanf ("%d", &t);
  
    while (t--) {
      scanf ("%lld %lld", &m, &n);
      solve(m, n);
      if (t) printf("\n");
    }
}
 