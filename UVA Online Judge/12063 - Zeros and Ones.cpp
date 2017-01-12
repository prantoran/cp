#include<bits/stdc++.h>
#define ll long long 
using namespace std;

int t,n,k,done[69][69][111],ca;
ll dp[69][69][111],ans;

ll f(int o,int z,int r){
    if(abs(o-z)>n-o-z)return 0;
    if(o+z==n)return r==0;
    if(done[o][z][r]==ca)return dp[o][z][r];
    done[o][z][r]=ca;
    ll ret = 0;
    ret+=f(o+1,z,(r*2+1)%k);
    if(o+z>0){
        ret+=f(o,z+1,(r*2)%k);
    }
    return dp[o][z][r]=ret;
}

int main(){
    freopen("in.txt","r",stdin);
    scanf("%d",&t);
    ca=0;

    while(t--){
        ca++;
        scanf("%d %d",&n,&k);
        if(n&1 || k==0)ans=0;
        else ans = f(0,0,0);
        printf("Case %d: %lld\n",ca,ans);
    }
    return 0;
}
