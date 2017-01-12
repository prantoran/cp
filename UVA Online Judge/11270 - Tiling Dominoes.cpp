#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int n, m,ca;

int done[12][111][2222];
ll ans,dp[12][111][2222];

ll f(int p,int h,int cm){
    if(p>=n){
        return f(0,h+1,cm);
    }
    if(h>=m){
        return cm == 0;
    }
    if(done[p][h][cm]==ca)return dp[p][h][cm];
    done[p][h][cm]=ca;
    ll ret = 0;

    if(!(cm&(1<<p))){
        ret+=f(p+1,h,cm|(1<<p));
        if(p+1<n && !(cm&(1<<(p+1)))){
            ret+=f(p+2,h,cm);
        }
    }
    else{
        ret+=f(p+1,h,cm^(1<<p));
    }
    return dp[p][h][cm]=ret;
}


int main(){
    freopen("in.txt","r",stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ca=0;
    while(cin>>n>>m){
        ca++;
        if(n>m)swap(n,m);

        ans = f(0,0,0);
        cout<<ans<<"\n";
    }


    return 0;
}
