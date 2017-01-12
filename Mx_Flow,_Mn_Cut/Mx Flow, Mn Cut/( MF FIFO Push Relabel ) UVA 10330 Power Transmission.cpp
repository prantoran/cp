//UVA 10330

#include<bits/stdc++.h>

#define sf scanf
#define pf printf

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

int n;

int source,sink,m;
int b,d;
int main(){

    #ifdef prantoran
        freopen("input.txt","r",stdin);
    #endif // prantoran
    int buffer = 111;
    source = 0;
    sink = 250;
    
    while(sf("%d",&n)!=EOF){
       // cout<<"n:"<<n<<endl;
        PushRelabel G = PushRelabel(300);
        
        for(int i = 1 , val;i<=n;i++){
            sf("%d",&val);
           // cout<<"i:"<<i<<"i+buf:"<<i+buffer<<"\tval:"<<val<<endl;
            G.AddEdge(i,i+buffer,val);
        }
        
        sf("%d",&m);
        for(int i = 0 , u ,v,val;i<m;i++){
            sf("%d %d %d",&u,&v,&val);
           // cout<<"\tu:"<<u<<"\tubuf:"<<u+buffer<<"\tv:"<<v<<"\tvbuf:"<<v+buffer<<"\tval:"<<val<<endl;
            
            G.AddEdge(u+buffer,v,val);
            //G.AddEdge(v+buffer,u,val);
        }
        //cout<<"m:"<<m<<endl;
        
        sf("%d %d",&b,&d);
        for(int i=0 , u ; i<b;i++){
            sf("%d",&u);
            //cout<<"(source,"<<u<<"}\n";
            G.AddEdge(source,u,(1<<30));
        }
        //cout<<"b:"<<b<<"\td:"<<d<<endl;
        
        
        for(int i=0 , u ; i<d;i++){
            sf("%d",&u);
           // cout<<"("<<u+buffer<<",sink)\n";
            G.AddEdge(u+buffer,sink,(1<<30));
        }
        //cout<<"done\n";
        cout<<G.GetMaxFlow(source,sink)<<"\n";
        //pf("%lld\n",G.GetMaxFlow(source,sink));
    }

    return 0;
}
