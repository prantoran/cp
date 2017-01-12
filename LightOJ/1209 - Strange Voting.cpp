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

int t,ca,m,f,vv;
vector<int> M[111],notM[111],F[111],notF[111];
string x,y;


int findID(string p){
    int ret = 0;
    int n = p.length();
    for(int i = 1;i<n;i++){
        ret *=10;
        ret += (p[i]-'0');
    }
    return ret;
}

int main(){
    freopen("in.txt","r",stdin);
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>t;
    for(ca=1;ca<=t;ca++){
        cin>>m>>f>>vv;
        U=0,V=0;
        for(int i = 1;i<=m;i++){
            M[i].clear();
            notM[i].clear();
        }
        for(int i = 1;i<=f;i++){
            F[i].clear();
            notF[i].clear();
        }
        for(int i = 1,mid,fid;i <=vv;i++){
            cin>>x>>y;
            if(x[0]=='M'){
                U++;
                fid = findID(y);
                mid = findID(x);
                notF[fid].push_back(U);
                M[mid].push_back(U);
            }
            else{
                V++;
                fid = findID(x);
                mid = findID(y);
                F[fid].push_back(V);
                notM[mid].push_back(V);
            }
        }
        for(int u = 1;u<=U;u++)Adj[u].clear();

        for(int i = 1,l1,l2;i<=f;i++){
            l1 = F[i].size(); l2 = notF[i].size();
            for(int j = 0,cu;j<l2;j++){
                cu = notF[i][j];
                for(int k = 0,cv;k<l1;k++){
                    cv = F[i][k];
                    Adj[cu].push_back(cv);
                }
            }
        }

        for(int i = 1,l1,l2;i<=m;i++){
            l1 = M[i].size(); l2 = notM[i].size();
            for(int j = 0, cu;j<l1;j++){
                cu = M[i][j];
                for(int k = 0, cv;k<l2;k++){
                    cv = notM[i][k];
                    Adj[cu].push_back(cv);
                }
            }
        }
        cout<<"Case "<<ca<<": "<<(vv-Hopcroft_Karp())<<"\n";
    }
    return 0;
}