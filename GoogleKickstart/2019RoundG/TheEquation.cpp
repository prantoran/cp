//https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050e02/000000000018fe36

#include <bits/stdc++.h>
using namespace std;

const int MX = 1024;

long long a[MX];

long long ones[51], zeros[51];

long long pow2[51];

long long f[51]; // minimum value of sum for all bits j <= i

int main () {

    freopen("data.in", "r", stdin);
    pow2[0] = 1;
    for (int i = 1; i < 51; i ++) 
        pow2[i] = pow2[i-1]*2;
    
    int t, n;
    long long m;

    scanf("%d", &t);
    
    for (int ca = 1; ca <= t; ca ++) {
        scanf ("%d %lld", &n, &m);
        for (int i = 0; i < n; i ++) {
            scanf ("%lld", &a[i]);
        }
        
        for (int i = 0; i < 51; i ++) {
            ones[i] = 0;
            zeros[i] = 0;
            
            long long mask = (long long)1<<i;

            for (int j = 0; j < n; j ++) {
                if (a[j] & mask) {
                    ones[i] ++;
                } else {
                    zeros[i] ++;
                }
            }
        }
        
        for (int i = 0; i < 51; i ++) {
            f[i] = 0;
            if (i) f[i] = f[i-1];
            if (ones[i] > zeros[i]) {
                f[i] += pow2[i]*zeros[i];
            } else {
                f[i] += pow2[i]*ones[i];
            }
        }
        
        long long ans = -1;

        if (f[50] <= m) {
            ans = 0;
            for (int i = 50; i >= 0; i --) {
                // careful of overflows
                long long u = pow2[i]*zeros[i];
                long long v = pow2[i]*ones[i];
                long long prev = 0;
                if (i) prev = f[i-1];
                if (u+prev > m) {
                    m -= v;
                } else {
                    ans |= ((long long)1<<i);
                    m -= u;
                }
            }
        }
        
        printf("Case #%d: %lld\n", ca, ans);
    }
    
    return 0;
    
}
