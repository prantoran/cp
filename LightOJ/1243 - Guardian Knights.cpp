#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define inf (ll)1<<30
#define SET(p) memset(p, -1, sizeof(p))
#define ff first 
#define ss second

#define MEM(p, v) memset(p, v, sizeof(p))

const int INF = 0x7f7f7f7f;
/*
min cost flow (bellman ford)
works only on directed graphs
handles multiple edges, cycles, loops
*/
const int MAXN = 300;
const int MAXE=100000;

int km[28][109];
 
int src, snk, nNode, nEdge;
int fin[MAXN], pre[MAXN], dist[MAXN];
int cap[MAXE], cost[MAXE], nxt[MAXE], to[MAXE], from[MAXE];
 
inline void init(int _src, int _snk, int nodes) {
    SET(fin);
    nNode = nodes, nEdge = 0;
    src = _src, snk = _snk;
}
 
inline void addEdge(int u, int v, int _cap, int _cost) {
    from[nEdge] = u, to[nEdge] = v, cap[nEdge] = _cap, cost[nEdge] = _cost;
    nxt[nEdge] = fin[u], fin[u] = nEdge++;
    from[nEdge] = v, to[nEdge] = u, cap[nEdge] = 0, cost[nEdge] = -(_cost);
    nxt[nEdge] = fin[v], fin[v] = nEdge++;
}
 
bool bellman() {
    int iter, u, v, i;
    bool flag = true;
    MEM(dist, 0x7f);
    SET(pre);
    dist[src] = 0;
    for(iter = 1; iter < nNode && flag; iter++) {
        flag = false;
        for(u = 0; u < nNode; u++) {
            for(i = fin[u]; i >= 0; i = nxt[i]) {
                v = to[i];
                if(cap[i] && dist[v] > dist[u] + cost[i]) {
                    dist[v] = dist[u] + cost[i];

                    pre[v] = i;
                    flag = true;
                }
            }
        }
    }
    return (dist[snk] < INF);
}
 
int mcmf(int &fcost) {
    int netflow, i, bot, u;
    netflow = fcost = 0;
    while(bellman()) {
        bot = INF;
        for(u = pre[snk]; u >= 0; u = pre[from[u]]) bot = min(bot, cap[u]);
        for(u = pre[snk]; u >= 0; u = pre[from[u]]) {
            cap[u] -= bot;
            cap[u^1] += bot;
            fcost += bot * cost[u];
        }
        netflow += bot;
    }
    return netflow;
}

int ca,t,n,k,m,mdx,ans,mxflow;
char grid[33][33];
pair<int,int>kpos[28],mpos[109];
int gm[33][33];
int p[28];

int mark[33][33];

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

int dis[33][33];

void bfs(int node){
    queue<pair<int,int> >q;
    q.push(kpos[node]);
    mark[kpos[node].ff][kpos[node].ss]=node+1;
    MEM(dis, 0x7f);
    dis[kpos[node].ff][kpos[node].ss]=0;

    while(!q.empty()){
        int x = q.front().ff;
        int y = q.front().ss;
        q.pop();

        for(int i = 0 ; i < 4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx<0 || ny<0 || nx==n || ny==n)continue;
            if(grid[nx][ny]=='#' || mark[nx][ny]==(node+1))continue;
            dis[nx][ny]=dis[x][y]+1;
            mark[nx][ny]=(node+1);
            if(grid[nx][ny]=='m'){
                km[node][gm[nx][ny]]=dis[nx][ny];
            }
            q.push({nx,ny});
        }
    }  
}


int main(){
    //freopen("in.txt","r",stdin);
    scanf("%d",&t);
    for(ca=1;ca<=t;ca++){
        scanf("%d %d %d ",&n,&k,&m);
        mdx=0;
        for(int i = 0 ; i < n;i++ ) {
            scanf("%s",grid[i]);
            for(int j = 0,id ; j < n;j++){
                if(grid[i][j]>='A' && grid[i][j]<='Z'){
                    id = grid[i][j]-'A';
                    kpos[id]={i,j};
                }
                else if(grid[i][j]=='m'){
                    gm[i][j]=mdx;
                    mpos[mdx++]={i,j};
                }
            }
        }
        for(int i = 0 ; i < k;i++)scanf("%d",&p[i]);

        MEM(mark,0);
        MEM(km, 0x7f);
        for(int i = 0 ;  i <k;i++){
            bfs(i);
        }
        init(0,m+k+1,m+k+3);
        for(int i = 0;i<k;i++){
            addEdge(src,i+1,p[i],0);
            for(int j = 0 ; j < m;j++){
                if(km[i][j]!=INF)
                    addEdge(i+1,j+k+1,p[i],km[i][j]);
            }
        }
        for(int i = 0 ;i < m;i++){
            addEdge(i+k+1,snk,1,0);
        }
        mxflow = mcmf(ans);
        printf("Case %d: %d\n",ca,ans);

    }
    return 0;
}