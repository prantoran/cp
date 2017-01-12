//UVA 10480 Sabotage

#include<bits/stdc++.h>

#define inf 1<<30
#define vi vector<int>
#define pb push_back

using namespace std;

const int mxn = 111;

int n , m;
int cap[mxn][mxn],flow[mxn][mxn];
vector<vi> adjlist;
int source, sink;

int maxFlow,curFlow;
vi p;

set<int>SSet;
bitset<mxn>dfsVis;

void dfs(int u){
    dfsVis.set(u);SSet.insert(u);
    for(auto v:adjlist[u])
        if(!dfsVis.test(v)&&(cap[u][v]-flow[u][v]>0))
            dfs(v);
}

void mincut(){
    SSet.clear();
    for(int i = 0 ; i < mxn;i++)dfsVis.reset();
    dfs(source);
    for(auto u:SSet)
        for(auto v:adjlist[u]){
            if(SSet.count(v))continue;
            if(cap[u][v]-flow[u][v]<=0)
                printf("%d %d\n",u,v);
        }
    printf("\n");
}

void augment(int v,int minEdge){
    if(v==source){curFlow=minEdge;return;};
    if(p[v]!=-1){
        augment(p[v],min(minEdge,cap[p[v]][v]-flow[p[v]][v]));
        flow[p[v]][v]+=curFlow;
        flow[v][p[v]]-=curFlow;
    }
}

void EdmondKarps(){
    maxFlow = 0 ;
    while(1){
        curFlow = 0 ;
        bitset<mxn>visited;
        visited.set(source);
        queue<int>q;
        q.push(source);
        p.assign(mxn,-1);
        while(!q.empty()){
            int u = q.front();q.pop();
            if(u==sink)break;
            for(auto v:adjlist[u])
                if(flow[u][v]<cap[u][v] && !visited.test(v)){
                    visited.set(v);
                    q.push(v);
                    p[v]=u;
                }
        }
        augment(sink,inf);
        if(!curFlow)break;
        maxFlow+=curFlow;
    }
}

int main(){
    #ifdef prantoran
        freopen("input.txt","r",stdin);
    #endif // prantoran

    while(scanf("%d %d",&n,&m),n||m){
        memset(cap,0,sizeof cap);
        memset(flow,0,sizeof flow);
        adjlist.assign(n+3,vi());
        source = 1 , sink = 2;
        for(int i = 0,u,v,w ; i < m ; i++){
            scanf("%d %d %d",&u,&v,&w);
            cap[u][v]+=w;
            cap[v][u]+=w;
            adjlist[u].pb(v);
            adjlist[v].pb(u);

        }
        EdmondKarps();
        mincut();
    }

}
