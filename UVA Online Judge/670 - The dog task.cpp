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
 
 
int t,n,m;
#define ll long long 
ll mx[222],my[222],nx[222],ny[222],nd[222];

ll dis(int i,int j){
    return (nx[i]-mx[j])*(nx[i]-mx[j]) + (ny[i]-my[j])*(ny[i]-my[j]);
}

 
int main(){
    freopen("in.txt","r",stdin);
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m);
        for(int i = 1;i<=n;i++){
            scanf("%lld %lld",&nx[i],&ny[i]);
        }
        for(int i = 1;i<=m;i++){
            scanf("%lld %lld",&mx[i],&my[i]);
        }

        for(int i = 1;i<n;i++){
            nd[i]=(nx[i+1]-nx[i])*(nx[i+1]-nx[i]) + (ny[i+1]-ny[i])*(ny[i+1]-ny[i]);
        }
        U = n-1;
        V = m;
        for(int i = 0 ;i <=U;i++)Adj[i].clear();

        for(int i = 1;i<=U;i++){
            for(int j = 1;j<=V;j++){
                if(sqrt(dis(i,j))+sqrt(dis(i+1,j))<=2*sqrt(nd[i])){    
                    Adj[i].push_back(j);
                }
            }
        }
        printf("%d\n",n+Hopcroft_Karp());

        for(int i = 1;i<n;i++){
            printf("%lld %lld ",nx[i],ny[i]);
            if(Pair_U[i]!=NIL)printf("%lld %lld ",mx[Pair_U[i]],my[Pair_U[i]]);
        }
        printf("%lld %lld\n",nx[n],ny[n]);
        if(t)printf("\n");
    }
    
    return 0;
} 