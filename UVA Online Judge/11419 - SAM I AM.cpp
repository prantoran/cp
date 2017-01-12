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

bool dU[mxn],dV[mxn];

void findMinimumVertexCover(){
    queue< pair<int,int> > q;
    memset(dU,0,sizeof(dU));
    memset(dV,0,sizeof(dV));
    for(int i = 1;i<=U;i++){
        if( Pair_U[i]==NIL ){
            dU[i]=1;
            q.push( {i,1});
        }
    }

    while(!q.empty()){
        int u = q.front().first;
        int id = q.front().second;
        q.pop();

        if(id == 1){
            for(int v, i = 0 , len = Adj[u].size(); i < len; i++ ) {
                v = Adj[u][i];
                if(!dV[v]){
                    dV[v]=1;
                    q.push({v,2});
                }
            }
        }
        else{
            if(!dU[Pair_V[u]]){
                dU[Pair_V[u]]=1;
                q.push({Pair_V[u],1});
            }
        }
    }
}

 
 int r,c,n;


int main(){
    freopen("in.txt","r",stdin);
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    while(scanf("%d %d %d",&r,&c,&n)!=EOF,r||c||n){
        U = r;
        V = c;
        for(int i = 0 ; i <= U;i++)Adj[i].clear();
        
        for(int i = 0 , u,v;i<n;i++){
            scanf("%d %d",&u,&v);
            Adj[u].push_back(v);

        }
        int matches = Hopcroft_Karp();

        findMinimumVertexCover();
        printf("%d",matches);
        
        for(int i = 1;i<=U;i++){
            if(!dU[i]){
                printf(" r%d",i);
            }
        }
        for(int i = 1;i<=V;i++){
            if(dV[i]){
                printf(" c%d",i);
            }
        }
        printf("\n");
    }
    
    return 0;
} 