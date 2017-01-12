#include<bits/stdc++.h>
#define mod 1000000007
#define ll long long
using namespace std;
ll a,b;

int ca,done[20][2][2][12],len;
pair<ll,ll> dp[20][2][2][12];

ll digsum[15];
ll cur[66];

pair<ll,ll> f(int pos ,int boundary,int nonzero,int lastdigit){
    if(pos>=len){
        return {nonzero,0};
    }
    if(done[pos][boundary][nonzero][lastdigit]==ca)
        return dp[pos][boundary][nonzero][lastdigit];
    done[pos][boundary][nonzero][lastdigit]=ca;

    ll permcnt = 0, maxdig=9;
    ll sum = 0;
    pair<ll,ll>tmp;
    if(boundary){
        maxdig=cur[pos];
    }
    
    for(int i = 0 ; i  <=maxdig;i++){
        tmp = f(pos+1,boundary&(cur[pos]==i),nonzero|(i!=0),i );
        permcnt += tmp.first;
        sum +=tmp.second;
        sum +=tmp.first * i;
    }
    return dp[pos][boundary][nonzero][lastdigit]={permcnt,sum};
}


int main(){

    //freopen("in.txt","r",stdin);
    ca=1;   
    digsum[0]=0;
    for(int i = 1;i<10;i++){
        digsum[i]=digsum[i-1]+i;
    } 
    memset(done,0,sizeof(done));

    while(scanf("%lld %lld",&a,&b),a||b){
        len=0;
        while(b){
            cur[len++]=b%10;
            b/=10;
        }
        reverse(cur,cur+len);
    
        ll ans = 0;
        pair<ll,ll> ci = f(0,1,0,0);
        ans = ci.second;
        ca++;
        a--;
        if(a>0){
            len=0;
            while(a){
                cur[len++]=a%10;
                a/=10;
            }
            reverse(cur,cur+len);
            ci = f(0,1,0,0);

            ans-=ci.second;
            ca++;
        }
        printf("%lld\n",ans);

    }
}