#include<bits/stdc++.h>
using namespace std;
 
//Lemma:
const int mxn = 111111;
const int inf = 1<<30;
const int NIL = 0; //extra node, all unassigned nodes assigned
int Pair_U[mxn],Pair_V[mxn];
int Dist[mxn]; // always on U
int U,V; //starts from 1
 
queue<int>Q;
vector<int>Adj[mxn]; //directed edge from u in U to v in V
 
bool BFS(){
    while(!Q.empty())Q.pop();
    for(int u = 1;u<=U;u++){
        if(Pair_U[u]==NIL){
            Dist[u]=0;
            Q.push(u);
        }
        else{
            Dist[u]=inf;
        }
    }
    Dist[NIL]=inf;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        if(Dist[u] < Dist[NIL]){
            for(int v,i = 0,len=Adj[u].size() ; i  <len;i++){
                v=Adj[u][i];
                if( Dist[Pair_V[v]] == inf ){
                    Dist[ Pair_V[v] ] = Dist[u] + 1;
                    Q.push(Pair_V[v]);
                }
            }
        }
    }
    return Dist[NIL] != inf; //Dist of NIL is not inf then an unmatched node in V is found
 
}
 
bool DFS(int u){
    if( u!= NIL ) {
        for(int v,i = 0,len=Adj[u].size() ; i  <len;i++){
            v = Adj[u][i];
            if(Dist[ Pair_V[v] ] == Dist[u] + 1){
                if ( DFS(Pair_V[v]) ){
 
                    Pair_V[v]=u;
                    Pair_U[u]=v;
                    return true;
                }
            }
        }
        Dist[u]=inf;
        return false;
    }
    //NIL node reached, hence free node in V found
    return true;
}
 
int Hopcroft_Karp(){
    for(int u = 1;u<=U;u++){
        Pair_U[u]=NIL;
    }
    for(int v = 1;v<=V;v++){
        Pair_V[v]=NIL;
    }
    int matching = 0;
    while( BFS() ) {
        for(int u = 1;u<=U;u++){
            if(Pair_U[u] == NIL ){
                if ( DFS(u) ){
                    matching=matching+1;
                }
            }
        }
    }
    return matching;
}
//complexity of one while loop: O( (V+E)//bfs + (V+E)//dfs)
//,, ,, all while loop at worst case: O( V*(V+E) ) ~ O(VE)
 
 
int n,m;
#define ll long long 
double s,vv;
 

 double nx[222],ny[222],mx[222],my[222];

 double dis(int i,int j){
    return (nx[i]-mx[j])*(nx[i]-mx[j]) + (ny[i]-my[j])*(ny[i]-my[j]);
 }
 
int main(){
    freopen("in.txt","r",stdin);
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    while(scanf("%d %d %lf %lf",&n,&m,&s,&vv)!=EOF){
        for(int i = 1 ; i <= n;i++){
            scanf("%lf %lf",&nx[i],&ny[i]);
        }
        for(int i = 1;i<=m;i++){
            scanf("%lf %lf",&mx[i],&my[i]);
        }
        U=n,V=m;

        s*=vv;
        s=s*s;

        for(int i = 0;i<=U;i++)Adj[i].clear();

        for(int i =1;i<=U;i++){
            for(int j = 1;j<=V;j++){
                if(dis(i,j)<=s){
                    Adj[i].push_back(j);
                }
            }
        }
        printf("%d\n",n-Hopcroft_Karp());
    }
    return 0;
} 