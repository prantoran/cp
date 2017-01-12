#include<bits/stdc++.h>
using namespace std;

const int mxn = 69;
vector<int>lt[mxn],rt[mxn];
int n,T,goingR[mxn],goingL[mxn],M1,M2,ca;

int done[mxn][699],dp[mxn][699];

const int inf = 1<<30;

int f(int pos,int curtime){
    if(curtime>T)return inf;
    if(curtime==T){
        if(pos==n-1)return 0;
        return inf;
    }
    if(done[pos][curtime]==ca){
        return dp[pos][curtime];
    }
    done[pos][curtime]=ca;
    int ans = inf;

    for(int i = 0 , len = lt[pos].size();i<len;i++){
        if(lt[pos][i]>=curtime){
            ans=min(ans, lt[pos][i]-curtime+f(pos-1,lt[pos][i]+goingL[pos-1]));
        }
    }
    for(int i = 0 , len = rt[pos].size();i<len;i++){
        if(rt[pos][i]>=curtime){
            ans=min(ans, rt[pos][i]-curtime+f(pos+1,rt[pos][i]+goingR[pos+1]));
        }
    }
    if(pos==(n-1)){
        ans=min(ans, T-curtime);
    }
    return dp[pos][curtime]=ans;
}

int main(){
   // freopen("in.txt","r",stdin);
    ca=0;
    while(scanf("%d",&n)){
        //cout<<"n:"<<n<<endl;
        ca++;
        if(n==0)break;
        scanf("%d",&T);
        memset(goingL,0,sizeof(goingL));
        memset(goingR,0,sizeof(goingR));

        for(int i = 1;i<n;i++){
            scanf("%d",&goingR[i]);
            goingL[i-1]=goingR[i];

        }
        for(int i = 0 ; i < mxn;i++){
            lt[i].clear();
            rt[i].clear();
        }

        scanf("%d",&M1);
        for(int i = 0,d ; i < M1;i++){
            scanf("%d",&d);
            for(int j =0 ;j<n-1;j++){
                rt[j].push_back(d);
                d+=goingR[j+1];
            }
        }

        scanf("%d",&M2);
        for(int i = 0,e;i<M2;i++){
            scanf("%d",&e);
            for(int j = n-1;j>0;j--){
                lt[j].push_back(e);
                e+=goingL[j-1];
            }
        }
        int ans = f(0,0);
        printf("Case Number %d: ",ca);
        if(ans==inf){
            printf("impossible\n");
        }
        else{
            printf("%d\n",ans);
        }

    }

    return 0;
}
