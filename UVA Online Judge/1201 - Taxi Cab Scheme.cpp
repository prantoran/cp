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

struct ride{
    int start, finish,a,b,c,d;
    ride(){}
    ride(int _s,int _a,int _b,int _c,int _d){
        start = _s;
        a = _a, b = _b, c = _c, d = _d;
        finish = abs(a-c)+abs(b-d)+start;
    }
    int minutesNeeded(ride& p){
        return abs(c-p.a) + abs(d-p.b);
    }
    bool canGo(ride& p){
        return ((minutesNeeded(p)+finish) < p.start); //must be 1 minute earlier, hence not (<=)
    }

};

int t,m,ca,hh,mm,a,b,c,d;
vector<ride>rides;

int main(){
    freopen("in.txt","r",stdin);
    //ios_base::sync_with_stdio(0);cin.tie(0);
    scanf("%d",&t);
    for(ca=1;ca<=t;ca++){
        scanf("%d",&m);
        rides.clear();
        U = m;
        V = m;
        for(int u = 0 ; u<=U;u++)Adj[u].clear();
        for(int i = 0 ; i < m;i++){
            scanf("%d:%d %d %d %d %d",&hh,&mm,&a,&b,&c,&d);
            rides.push_back(ride(hh*60+mm,a,b,c,d));
        }

        for(int i = 0 ;i < m;i++){
            for(int j = 0 ; j < m;j++){
                if(i==j)continue;
                if(rides[i].canGo(rides[j])){
                    Adj[i+1].push_back(j+1);
                }
            }
        }
        printf("%d\n",m - Hopcroft_Karp());
    }
    return 0;
}