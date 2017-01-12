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
vector<int>Adj[mxn]; //directed, from u in U to v in V

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

//###################SCC-TARJAN###########################//

int ca,t,m,n;

const int MAX = 2222;

int Stack[MAX],top;
int Index[MAX],Lowlink[MAX], Onstack[MAX];
int Component[MAX];
int idx,components;
vector<int> G[MAX],G2[MAX];

void tarjan(int u){
    int v,i,len;
    Index[u]=Lowlink[u] = idx++;
    Stack[top++] = u;
    Onstack[u] = 1;
    for(i = 0,len = G[u].size();i<len;i++){
        v = G[u][i];
        if( Index[v] == -1){
            tarjan(v);
            Lowlink[u] = min(Lowlink[u],Lowlink[v]);
        }
        else if(Onstack[v])Lowlink[u]=min(Lowlink[u],Index[v]);
    }
    if(Lowlink[u] == Index[u]){
        components ++ ;
        do{
            v = Stack[--top];
            Onstack[v] = 0;
            Component[v] = components;
        }while(u!=v);

    }
}

void findSCC(int n){
    components = top = idx = 0;
    memset(Index,-1,sizeof(Index));
    memset(Onstack,0,sizeof(Onstack));
    memset(Lowlink,0x3f,sizeof(Lowlink));
    for(int i = 1; i<=n;i++)if(Index[i]==-1)tarjan(i);
}

//###########################################################//


bool vis[MAX];
void BFS(int u){
    queue<int>Q;
    memset(vis,0,sizeof(vis));
    vis[u]=1;
    Q.push(u);
    while(!Q.empty()){
        int ci = Q.front();
        Q.pop();
        for(int i = 0 , v, len = G2[ci].size();i<len;i++){
            v = G2[ci][i];
            if(vis[v])continue;
            vis[v]=true;
            G[u].push_back(v);
            Q.push(v);
        }
    }
}

int main(){
    freopen("in.txt","r",stdin);
    scanf("%d",&t);
    for(ca=1;ca<=t;ca++){
        scanf("%d %d",&n,&m);
        for(int i = 0 ; i<=n;i++){
            G[i].clear();
            G2[i].clear();
            Adj[i].clear();
        }
        for(int i = 0 , u , v;i<m;i++){
            scanf("%d %d",&u,&v);
            G2[u].push_back(v);
        }
        for(int i = 1;i<=n;i++)
            BFS(i);
        findSCC(n);
        U = n; V = n;
        for(int u = 1;u<=U;u++){
            for(int i = 0 , len = G[u].size(),v;i<len;i++){
                v = G[u][i];
                if( Component[u] != Component[v]){
                    Adj[Component[u]].push_back(Component[v]);
                }
            }
        }
        printf("Case %d: %d\n",ca,components-Hopcroft_Karp());
    }
    return 0;
}