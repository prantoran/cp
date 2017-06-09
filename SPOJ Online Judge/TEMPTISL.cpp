#include<bits/stdc++.h>
#define ll long long 
using namespace std;

int dn[69][69];
ll dp[69][69];
int ca;
int n,k,a,b;

ll f(int p, int rem) {
    if(rem == 0) {
        if( p == b ) return 1;
        return 0;
    }
    if( dn[p][rem] == ca ) return dp[p][rem];
    dn[p][rem] = ca;
    ll ret = f((p-1+n)%n, rem -1) + f((p+1)%n, rem -1);
    return dp[p][rem] = ret;
}

int main() {
    freopen("in.txt", "r", stdin);
    while(scanf("%d %d", &n, &k)) {
        if(n==-1 && k == -1) break;
        ca ++;
        scanf("%d %d",&a, &b);
        a--, b--;
        printf("%lld\n", f(a,k));

    }

    return 0;
}