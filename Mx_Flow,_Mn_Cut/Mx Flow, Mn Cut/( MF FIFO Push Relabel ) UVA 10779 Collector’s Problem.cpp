//UVA 259 Software Allocation

#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
  int N;
  vector<vector<Edge> > G;
  vector<LL> excess;
  vector<int> dist, active, count;
  queue<int> Q;

  PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(int from, int to, int cap) { //adds directed edge (from, to)
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }

  void Enqueue(int v) {
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
  }

  void Push(Edge &e) {
    int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;
    excess[e.from] -= amt;
    Enqueue(e.to);
  }

  void Gap(int k) {
    for (int v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  void Relabel(int v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (int i = 0; i < G[v].size(); i++)
      if (G[v][i].cap - G[v][i].flow > 0)
	dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

  void Discharge(int v) {
    for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1)
	Gap(dist[v]);
      else
	Relabel(v);
    }
  }

  LL GetMaxFlow(int s, int t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (int i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }

    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }

    LL totflow = 0;
    for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
};

int t, n , m,ca;
int cnt[69];
int source,sink;

int main(){

    #ifdef prantoran
        freopen("input.txt","r",stdin);
    #endif // prantoran

    /*
    source = 0
    1 - 10 ppl

    15-45 - sticker types

    50-90 - trading nodes

    95-125 - gain cards

    sink = 130
    */

    int stickerType = 15;
    int TradingNode = 50;
    int gainCard = 95;


    scanf("%d",&t);
    for(ca=1;ca<=t;ca++){
        scanf("%d %d",&n,&m);
        //cout<<"n:"<<n<<"m:"<<m<<endl;

        PushRelabel G = PushRelabel(150);

        source=0;  //bob
        sink = 130;





        for(int i = 1,cc ; i <= n ;i++ ) {
            memset(cnt,0,sizeof(cnt));
            scanf("%d",&cc);

            for(int j = 0,val ;  j< cc;j++){
                scanf("%d",&val);
                cnt[val]++;
            }

            if(i==1){

                for(int j = 1;j<=m;j++){
                    if(cnt[j]){
                        G.AddEdge(source,j+stickerType,cnt[j]);
                        G.AddEdge(j+stickerType,j+TradingNode,cnt[j]);
                    }
                }

            }
            else{
                for(int j = 1;j<=m;j++){
                    if(cnt[j]>1){
                        G.AddEdge(i,j+TradingNode,cnt[j]-1);
                    }
                    else if(!cnt[j]){
                        G.AddEdge(j+TradingNode,i,1);
                    }
                }
            }
        }
        for(int i = 1; i <=m;i++){
            G.AddEdge(i+TradingNode,i+gainCard,1);
            G.AddEdge(i+gainCard,sink,1);
        }
        cout<<"Case #"<<ca<<": "<<G.GetMaxFlow(source,sink)<<"\n";
    }

    return 0;
}
