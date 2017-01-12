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

int t,n,ca;
char grid[69][69];

pair<int,int> ghosts[mxn],humans[mxn];

bool valid[1111][1111];
int ghdis[1111][1111];
int hid[69][69];

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

int dn[69][69];

void bfs(int p){
    queue< pair<int,int> > q;
    q.push(ghosts[p]);
    
    for(int i = 0 ;i <n;i++)
        for(int j = 0 ;j < n;j++)
            dn[i][j]=inf;

    dn[ghosts[p].first][ghosts[p].second]=0;

    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i = 0 ; i < 4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx<0 || ny<0 || nx == n || ny==n)continue;
            if(dn[nx][ny]!=inf || grid[nx][ny]=='#')continue;
            dn[nx][ny]=dn[x][y]+1;
            q.push({nx,ny});
            if(grid[nx][ny]=='H'){
                valid[p][hid[nx][ny]]=1;
                ghdis[p][hid[nx][ny]]=dn[nx][ny];
            }
        } 
    }
}

int main(){
    freopen("in.txt","r",stdin);
    scanf("%d",&t);
    for(ca=1;ca<=t;ca++){
        scanf("%d ",&n);
        for(int i = 0 ;i < n;i++){
            scanf("%s",grid[i]);
        }
        U=0,V=0;
        for(int i = 0 ; i < n;i++){
            for(int j = 0 ; j < n;j++){
                if(grid[i][j]=='G'){
                    ghosts[++U]={i,j};
                }
                else if(grid[i][j]=='H'){
                    humans[++V]={i,j};
                    hid[i][j]=V;
                }
            }
        }
        memset(valid,0,sizeof(valid));
        for(int u = 1;u<=U;u++){
            bfs(u);
        }

        int lo = 3, hi = n*n*2;

        int ans = inf;

        while(lo < hi){
            int mid = (lo+hi)/2;
            for(int u = 1;u<=U;u++)Adj[u].clear();

            for(int i = 1;i<=U;i++){
                for(int j = 1;j<=V;j++){
                    if(valid[i][j] && (2+ghdis[i][j]*2<=mid) ){
                        Adj[i].push_back(j);
                    }
                }
            }
            if(Hopcroft_Karp() == V){
                hi = mid;
                ans = min(ans,mid);
            }
            else{
                lo = mid+1;
            }
        }
        if(ans==inf)printf("Case %d: Vuter Dol Kupokat\n",ca);
        else printf("Case %d: %d\n",ca,ans);

    }
    return 0;
}