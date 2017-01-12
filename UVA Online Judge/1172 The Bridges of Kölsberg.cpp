#include<bits/stdc++.h>
#define ll long long 
using namespace std;

const int mxn =1111;

int n,m,idx,t;
ll profit[2][mxn];
int os[2][mxn];
string buff;
map<string,int>id;
ll dp[mxn][mxn];
int cnt[mxn][mxn];

int main(){
    //freopen("in.txt","r",stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    while(t--){
        id.clear();
        idx=1;
        
        cin>>n;
        for(int i =1;i<=n;i++){
            cin>>buff>>buff>>profit[0][i];
            if(id[buff]==0)id[buff]=idx++;
            os[0][i]=id[buff];
        }

        cin>>m;
        for(int i =1;i<=m;i++){
            cin>>buff>>buff>>profit[1][i];
            if(id[buff]==0)id[buff]=idx++;
            os[1][i]=id[buff];
        }

        memset(dp,0,sizeof(dp));
        memset(cnt,0,sizeof(cnt));

        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=m;j++){
                dp[i][j]=dp[i-1][j];
                cnt[i][j]=cnt[i-1][j];
                if(dp[i][j-1]>dp[i][j]){
                    dp[i][j]=dp[i][j-1];
                    cnt[i][j]=cnt[i][j-1];
                }
                else if(dp[i][j-1] == dp[i][j]){
                    cnt[i][j]=min(cnt[i][j],cnt[i][j-1]);
                }
                if(os[0][i]==os[1][j]){
                    ll v1 = dp[i-1][j-1] + profit[0][i]+profit[1][j];
                    if(v1>dp[i][j]){
                        dp[i][j]=v1;
                        cnt[i][j]=cnt[i-1][j-1]+1;
                    }
                    else if(v1 == dp[i][j]){
                        cnt[i][j]= min(cnt[i][j],cnt[i-1][j-1]+1);
                    }
                }
            }
        }
        cout<<dp[n][m]<<" "<<cnt[n][m]<<"\n";
    }
    return 0;
}
