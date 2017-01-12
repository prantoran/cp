#include<bits/stdc++.h>
using namespace std;
 
const int N = 160, M = N*N*4, inf = 0x3f3f3f3f;
//s = source, t = sink, ne= edgeno [] not [)
int s, t, full, flow, cost;
int now, d[N], vis[N], instk[N], slack[N];
int ne, head[N], cur[N], vex[M], cap[M], cst[M], nxt[M];
 
void add_edge(int u, int v, int c, int w) {
  ++ne;
  vex[ne] = v;
  cap[ne] = c;
  cst[ne] = w;
  nxt[ne] = head[u];
  head[u] = ne;
}
void add_2edge(int u, int v, int c, int w) {
  add_edge(u, v, c, +w);
  add_edge(v, u, 0, -w);
}
 
int dfs(int u, int f) {
  if(u == t) { cost += f*d[t]; return f; }
  vis[u] = instk[u] = now;
  int sumf = 0;
  for(int& i = cur[u]; i; i = nxt[i]) if(cap[i]) {
    int v = vex[i], s = d[u]+cst[i]-d[v], rest = min(f-sumf, cap[i]);
    if(!rest) continue;
    //setmin(slack[v], s);
    if(slack[v]>s)slack[v]=s;
 
    if(!s && instk[v]!=now)
      if(int df = dfs(v, rest)) {
        cap[i  ] -= df;
        cap[i^1] += df;
        if((sumf+=df) == f) break;
      }
  }
  instk[u] = false;
  return sumf;
}
bool relabel() {
  int mins = inf;
  for(int i = 0 ; i <=t;i++) if(vis[i] != now) if(mins>slack[i]) mins=slack[i];
  if(mins == inf) return false;
  for(int i = 0 ; i <=t;i++) if(vis[i] != now) d[i] += mins;
  return true;
}
int zkwMCMF() {
  memset(d,0,sizeof(d)), flow = cost = 0;
  do {
    while(1) {
      memcpy(cur,head,sizeof(cur)), memset(slack,63,sizeof(slack)), ++now;
      if(int df=dfs(s, inf)) flow += df;
      else break;
    }
  } while(relabel());
  return flow;
}
int TT,n,c,r;
 
int main() {
   // freopen("in.txt","r",stdin);
    scanf("%d",&TT);
    for(int cas=1;cas<=TT;cas++) {
        scanf("%d %d %d",&n,&c,&r);
 
        memset(head,0,sizeof(head));    
        s = n+n+c, t = n+n+c+1, ne = 1, full = 0;
 
        for(int i = 0,u;i<n;i++){
            scanf("%d",&u);
            full+=u;
            add_2edge(i,t,u,0);
            add_2edge(s,i+n,u,0);
        }
        for(int i = 0, u,v; i < c;i++){
            scanf("%d %d",&u,&v);
            add_2edge(s,(n<<1) + i,u,v);  //car supplier: (2*n)+i
            for(int j = 0 ; j < n;j++){
                add_2edge((n<<1) + i,j,INT_MAX,0);
            }
        }
 
        for(int i = 0, u , v;i<r;i++){
            scanf("%d %d",&u,&v);
            for(int j = 0 ; j < n;j++){
                for(int k = j+u+1;k<n;k++){
                    add_2edge(n+j,k,INT_MAX,v);
                }
            }
        }
        printf("Case %d: ", cas);
        if(zkwMCMF()==full) printf("%d\n", cost);
        else  puts("impossible");
    }
    return 0;
}