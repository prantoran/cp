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

char a[333][333];

int ROW[333][333],COL[333][333];

int main(){
    freopen("in.txt","r",stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    while(t--){
        cin>>r>>c;
        for(int i = 0;i<r;i++){
            for(int j = 0 ; j  <c;j++){
                cin>>a[i][j];
            }
        }
        
        int idx = 0;
        for(int i = 0 ; i < r;i++){
            idx++;
            for(int j = 0 ; j < c;j++){
                if(a[i][j]=='A')idx++;
                ROW[i][j]=idx;
            }
        }
        U=idx;
        idx = 0;
        for(int j = 0 ; j < c;j++){
            idx++;
            for(int i =  0; i< r;i++){
                if(a[i][j]=='A')idx++;
                COL[i][j]=idx;
            }
        }

        V=idx;
        for(int i = 0 ; i<=V;i++){
            Adj[i].clear();
        }
        for(int i = 0;i<r;i++){
            for(int j = 0; j  <c;j++){
                if(a[i][j]=='H'){
                    Adj[ROW[i][j]].push_back(COL[i][j]);
                }
            }
        }
        printf("%d\n",Hopcroft_Karp());


    }



    return 0;
}