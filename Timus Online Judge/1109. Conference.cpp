//http://acm.timus.ru/problem.aspx?space=1&num=1109

#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<bits/stdc++.h>
using namespace std;

#define MAX 11111
#define NIL 0
#define INF (1<<28)

vector<int> G[MAX];
int n,m,lmatch[MAX],rmatch[MAX],dist[MAX];

bool bfs(){
    int i , u , v, len;
    queue<int>Q;
    for(i = 1;i<=n;i++){
        if(lmatch[i]==NIL){
            dist[i]=0;
            Q.push(i);
        }
        else dist[i]=INF;
    }
    dist[NIL]=INF;
    while(!Q.empty()){
        u = Q.front();Q.pop();
        if(u!=NIL){
            len = G[u].size();
            for(i=0;i<len;i++){
                v=G[u][i];
                if(dist[rmatch[v]]==INF){
                    dist[rmatch[v]]=dist[u]+1;
                    Q.push(rmatch[v]);
                }
            }
        }
    }
    return (dist[NIL]!=INF);
}

bool dfs(int u){
    int i , v , len;
    if(u!=NIL){
        len = G[u].size();
        for(i = 0 ; i < len ; i++ ) {
            v = G[u][i];
            if(dist[rmatch[v]]==dist[u]+1){
                if(dfs(rmatch[v])){
                    rmatch[v]=u;
                    lmatch[u]=v;
                    return true;
                }
            }
        }
        dist[u]=INF;
        return false;
    }
    return true;
}

int hopcroft_karp(){
    int matching = 0 , i ;
    memset(lmatch,0,sizeof(lmatch));
    memset(rmatch,0,sizeof(rmatch));
    int iter=1;
    while(bfs()){
        iter++;
        for(i = 1;i<=n;i++){
            if(lmatch[i]==NIL && dfs(i)){
                matching++;
            }
        }
    }
    return matching;
}
int N,M,K;
int fndL[MAX],fndR[MAX];

int main(){
    //freopen("in.txt","r",stdin);
   // freopen("out.txt","w",stdout);
    scanf("%d %d %d",&N,&M,&K);

    for(int i = 0 ; i <=N;i++)G[i].clear();
    n=0,m=0;
    memset(fndL,0,sizeof(fndL));
    memset(fndR,0,sizeof(fndR));

    for(int i = 0 , u , v ; i<K;i++){
        scanf("%d %d",&u,&v);
        if(!fndL[u]){
            fndL[u]=++n;
        }
        if(!fndR[v]){
            fndR[v]=++m;
        }
        G[fndL[u]].push_back(fndR[v]);
    }
    int bpm = hopcroft_karp();

    printf("%d\n",n+m-bpm);
    return 0;
}
