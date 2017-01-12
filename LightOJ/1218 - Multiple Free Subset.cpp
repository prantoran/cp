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

bool sk[mxn];

bool BFS(){
    while(!Q.empty())Q.pop();
    for(int u = 1;u<=U;u++){
        if(sk[u])continue;
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
        if(sk[u])continue;
        Q.pop();
        if(Dist[u] < Dist[NIL]){
            for(int v,i = 0,len=Adj[u].size() ; i  <len;i++){
                v=Adj[u][i];
                if(sk[v])continue;
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
    if(sk[u])return 0;
    if( u!= NIL ) {
        for(int v,i = 0,len=Adj[u].size() ; i  <len;i++){
            v = Adj[u][i];
            if(sk[v])continue;
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
            if(sk[u])continue;
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

int ca,t,n,a[222];
vector<int>ans;

int main(){
    freopen("in.txt","r",stdin);
    scanf("%d",&t);
    for(ca=1;ca<=t;ca++){
        scanf("%d",&n);
        for(int i = 1;i<=n;i++)scanf("%d",&a[i]);
        sort(a+1,a+1+n);

        U = n , V = n;
        for(int u = 0 ; u<=U;u++)Adj[u].clear();
        for(int i =  1; i<=U;i++){
            for(int j = i+1;j<=V;j++){
                if(a[j]%a[i] == 0)Adj[i].push_back(j);
            }
        }
        memset(sk,0,sizeof(sk));
        ans.clear();

        int mis = U - Hopcroft_Karp();
        U--;
        for(int i = U+1;i>0;i--){
            sk[i]=1;
            if((U-Hopcroft_Karp()) != mis){
                sk[i]=0;
                ans.push_back(a[i]);
            }
            else{
                U--;
            }
        }
        sort(ans.begin(),ans.end());
        printf("Case %d:",ca);
        for(int i = 0 ; i < mis;i++){
            printf(" %d",ans[i]);
        }printf("\n");


    }
    return 0;
}