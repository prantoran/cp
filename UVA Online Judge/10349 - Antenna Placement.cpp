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
 
 
int t,r,c;
char grid[50][12];
int color[50][12],mark[50][12];

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

int main(){
    freopen("in.txt","r",stdin);
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    memset(mark,0,sizeof(mark));
    for(int i = 0 ; i < 50;i++){
        for(int j = 0 ; j < 12;j++){
            color[i][j]= ( (i+j)%2 ) + 1; 
        }
    }
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&r,&c);
        for(int i = 0;i<r;i++){
            scanf("%s",grid[i]);
        }
        U = 0;
        V = 0;
        for(int i = 0 ; i  <r;i++){
            for(int j = 0 ; j < c;j++){
                if(grid[i][j]=='*'){
                    if(color[i][j]==1){
                        U++;
                        mark[i][j]=U;
                    }
                    else{
                        V++;
                        mark[i][j]=V;
                    }
                }
                else{
                    mark[i][j]=0;
                }
            }
        }
        for(int i = 0; i<=U;i++)Adj[i].clear();
        for(int i  =0,cu,cv ; i <r;i++){
            for(int j = 0; j < c;j++){
                if(mark[i][j]){
                    cu = mark[i][j];
                    if(color[i][j] == 1){ //node from set U
                        for(int k = 0; k< 4;k++){
                            int nx = i + dx[k];
                            int ny = j + dy[k];
                            if(nx<0 || ny<0 || nx==r || ny==c)continue;
                            if(mark[nx][ny]){
                                cv = mark[nx][ny];
                                Adj[cu].push_back(cv);
                            }
                        }
                    }
                }
            }
        }

        printf("%d\n",U+V-Hopcroft_Karp());

    }
    
    return 0;
} 