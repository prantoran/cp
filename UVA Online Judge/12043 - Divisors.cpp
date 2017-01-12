#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mxn = 111111;

bool sieve[mxn];
ll cnt,cur,cursum,curpow,divsum[mxn],divcnt[mxn];

int t;
ll a,b,k;

int main(){
   // freopen("in.txt","r",stdin);
    memset(sieve,0,sizeof(sieve));

    for(int i = 0;i<mxn;i++){
        divsum[i]=1;
        divcnt[i]=1;
    }
    for(ll i = 2,cnt;i<mxn;i+=2){
        cnt=0;
        curpow=1;
        cur = i;
        while(cur%2 == 0){
            cnt++;
            cur/=2;
            curpow*=2;
        }
        curpow*=2;
        curpow-=1;

        divsum[i]=curpow;
        divcnt[i]=cnt+1;
        sieve[i]=1;

    }
  //  cout<<"divsum[6]:"<<divsum[6]<<endl;
    for(ll i = 3;i<mxn;i++){
        if(sieve[i]==0){
            for(ll j = i;j<mxn;j+=i){
                cur=j;
                curpow=1;
                cnt=0;
                while(cur%i == 0){
                    cnt++;
                    cur/=i;
                    curpow*=i;
                }
                curpow*=i;
                curpow-=1;
                curpow/=(i-1);
                divsum[j]*=curpow;
                divcnt[j]*=(cnt+1);
                sieve[j]=1;

            }
        }
    }

//    for(int i =1;i<=30;i++){
//        cout<<"i:"<<i<<"\tcnt:"<<divcnt[i]<<"\tsum:"<<divsum[i]<<endl;
//    }


    scanf("%d",&t);
    while(t--){
        scanf("%lld %lld %lld",&a,&b,&k);
        cursum =0;
        cnt=0;

        ll p = a/k;

        if(p*k != a){
            p++;

        }
        p*=k;

        while(p<=b){
            cnt+=divcnt[p];
            cursum+=divsum[p];
            p+=k;
        }
        printf("%lld %lld\n",cnt,cursum);

    }


    return 0;
}