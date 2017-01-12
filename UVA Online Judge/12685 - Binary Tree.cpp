//Tag: DP + Tree + String

#include<bits/stdc++.h>
#define ll long long
#define mod 21092013
using namespace std;

const int mxn = 111111;

char S[mxn],T[mxn];
int t,n,lenT,lenS;
int nextL[mxn],nextR[mxn],nextU[mxn];
ll dp[mxn];

int main(){

   // freopen("in.txt","r",stdin);
    scanf("%d",&t);
    for(int ca=1;ca<=t;ca++){
        scanf("%s %s",&S,&T);
        //cout<<"S"<<S<<"\tT:"<<T<<endl;

        lenS=strlen(S);lenT=strlen(T);
        int p = 0;

        for(int i=0;i<lenS;i++){
           // cout<<"i:"<<i<<"\tS[i]:"<<S[i]<<endl;
            if(S[i]=='U'){
                if(p)p--;
            }
            else{

                S[p++]=S[i];
               // cout<<"en p:"<<p<<"\n";
            }
        }
        lenS=p;
        //cout<<"lenS:"<<lenS<<endl;
        nextL[lenT]=nextR[lenT]=nextU[lenT]=lenT;

        for(int i = lenT-1;i>=0;i--){
            nextL[i]=nextL[i+1];
            nextR[i]=nextR[i+1];
            nextU[i]=nextU[i+1];

            if(T[i]=='L')nextL[i]=i;
            else if(T[i]=='R')nextR[i]=i;
            else nextU[i]=i;
        }

        dp[lenT]=0;
        for(int i = lenT-1;i>=0;i--){
            dp[i]=(1+dp[nextL[i+1]]+dp[nextR[i+1]])%mod;
        }


//
//        for(int i = 0 ; i <=lenT;i++){
//            cout<<"dp["<<i<<"]:"<<dp[i]<<endl;
//        }

        ll ans = (1+dp[nextL[0]]+dp[nextR[0]])%mod;
        //cout<<"ans:"<<ans<<endl;
        int now = nextU[0];
       // cout<<"now:"<<now<<"\tlenS:"<<lenS<<endl;

        for(int i = 1;i<=lenS;i++){
           // cout<<"now:"<<now<<endl;
            if(now==lenT)break;
           // cout<<"S["<<lenS-i<<"]:"<<S[lenS-i]<<endl;
            if(S[lenS-i]=='L')ans = (ans+1+dp[nextR[now]])%mod;
            else ans = (ans + 1 + dp[nextL[now]])%mod;
            now = nextU[now+1];
        }
        printf("Case %d: %lld\n",ca,ans);



    }


}
