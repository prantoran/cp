//http://poj.org/problem?id=2942
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int mxn = 1111;

int n , m, enemies[mxn][mxn],curtime;
bool valid[mxn],visited[mxn];
int s[666666],stp; //stack
bool inStack[mxn];
int dfn[mxn],low[mxn];
int color[mxn];

bool belongsToOddCycle(int node){
    queue<int>q;
    q.push(node);
    memset(color,-1,sizeof(color));
    color[node]=1;
    while(!q.empty()){
        int curnode = q.front();
        q.pop();
        for(int i = 1;i<=n;i++){
            if(curnode==i || enemies[curnode][i] || !inStack[i])continue;
            if(color[i]==-1){
                color[i]=color[curnode]^1;
                q.push(i);
            }
            else if(color[i]==color[curnode])return true;
        }
    }
    return false;
}

void tarjan(int node,int parent){
    s[stp++]=node;
    dfn[node] = low[node] = curtime++;
    visited[node] = 1;
    for(int i = 1; i <=n;i++){
        if(i==node || i == parent || enemies[node][i])continue;
        if(visited[i])low[node]=min(low[node],dfn[i]);
        else{
            tarjan(i,node);
            low[node]=min(low[node],low[i]);
            if(low[i]>=dfn[node]){
                memset(inStack,0,sizeof(inStack));
                while(s[--stp]!=i){
                    inStack[s[stp]]=1;
                }
                inStack[i]=1;
                //new elements will be inserted at index where i is
                //which will automatically erase i
                inStack[node]=1;
                if(belongsToOddCycle(node)){
                    for(int i = 1;i<=n;i++){
                        if(inStack[i])valid[i]=1;
                    }
                }
            }
        }
    }
}

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%d %d",&n,&m)){
        if(n==0 && m == 0)break;
        memset(enemies,0,sizeof(enemies));
        for(int i = 0 , u , v ;i<m;i++){
            scanf("%d %d",&u,&v);
            enemies[u][v]=1;
            enemies[v][u]=1;
        }
        memset(visited,0,sizeof(visited));
        memset(valid,0,sizeof(valid));
        curtime=0,stp=0;
        for(int i = 1;i<=n;i++){
            if(!visited[i])tarjan(i,i); // find biconnected components
        }
        int ans =0;
        for(int i =1;i<=n;i++)if(!valid[i])ans++;
        printf("%d\n",ans);
    }
    return 0;
}
