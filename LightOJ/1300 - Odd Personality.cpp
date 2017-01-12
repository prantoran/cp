//http://lightoj.com/volume_showproblem.php?problem=1300
#include<bits/stdc++.h>
#define sz 10002
using namespace std;

int t,n,m,ca,uu,vv,k,cnt,dfsNumberCounter,component;
vector< vector<int> >adjlist;
int dfs_num[33][sz],dfs_low[sz];
set<pair<int,int> > bpairs;
int mark[33][sz];
 bool valid;

inline void bridge( int u, int parent ) {
    dfs_low[u] = dfs_num[ca][u] = ++dfsNumberCounter;
    for( int i = 0, l = adjlist[u].size() ; i < l; i++ ) {
        int v = adjlist[u][i];
        if(v^parent){
            if( !dfs_num[ca][v]  ) {
                bridge(v,u);
                if(dfs_low[v]>dfs_num[ca][u]){
                    bpairs.insert(make_pair(min(u,v),max(u,v)));
                }
                dfs_low[u] = min( dfs_low[u], dfs_low[v] );
            }
            else {
                dfs_low[u] = min( dfs_low[u], dfs_num[ca][v] );
            }
        }
    }
}

void dfs( int u ) {
    cnt++;
    for(int i=0,l=adjlist[u].size();i<l;i++){
        int v = adjlist[u][i];
        if(bpairs.find(make_pair(min(u,v),max(u,v)))!=bpairs.end())continue;
        if(mark[ca][v] && mark[ca][v]==mark[ca][u])valid=true;
        else if(!mark[ca][v]){
            mark[ca][v]=0-mark[ca][u];
            dfs(v);
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif // ONLINE_JUDGE

    scanf("%d",&t);
   for( ca = 1; ca <= t; ca++ ) {
        scanf("%d %d",&n,&m);
        adjlist = vector< vector<int> >(n+2);
        while(m--) {
            scanf("%d %d",&uu,&vv);
                uu++;vv++;

                adjlist[uu].push_back(vv);
                adjlist[vv].push_back(uu);

        }
        bpairs.clear();
        dfsNumberCounter = 0;
        for(int i = 1; i<=n;i++)if(!dfs_num[ca][i])bridge(i,i);
        component = 0 ;
        for(int i = 1; i <= n ; i++ ){
            if(!mark[ca][i]){
                valid=0;
                mark[ca][i]=-1;
                cnt=0;
                dfs(i);
                if(valid)component+=cnt;
            }
        }
        printf("Case %d: %d\n",ca,component);
    }
    return 0;
}
