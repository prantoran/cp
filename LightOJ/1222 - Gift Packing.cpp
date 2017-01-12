#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define inf (ll)1<<30
#define SET(p) memset(p, -1, sizeof(p))

#define MEM(p, v) memset(p, v, sizeof(p))

const int INF = 0x7f7f7f7f;
/*
min cost flow (bellman ford)
works only on directed graphs
handles multiple edges, cycles, loops
*/
const int MAXN = 300;
const int MAXE=100000;

 
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

int t,n,ca,des;
ll c;

int main(){
    freopen("in.txt","r",stdin);
    scanf("%d",&t);
    src=0;
    for(ca=1;ca<=t;ca++){
        scanf("%d",&n);
        
        //cout<<"des:"<<des<<endl;
        
        init(0,2*n +1,2*n + 4);
        for(int i = 1;i<=n;i++){
            addEdge(0,i,1,0);
            for(int j = n+1;j<=2*n;j++){
                scanf("%lld",&c);
               addEdge(i,j,1,2000-c);
            }
           addEdge(i+n,snk,1,0);

        }

        int mncost;
        int flow  =  mcmf(mncost);
        printf("Case %d: %d\n",ca,2000*n-mncost);
    }


    return 0;
}