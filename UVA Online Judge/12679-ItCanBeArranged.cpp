//UVA 12679 - It Can Be Arranged
// BPM
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
    //  cout<<"s:"<<s<<"\tt:"<<t<<endl;
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
     // cout<<"v:"<<v<<endl;
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

int source,sink,m,t;

const int mxn = 222;
int st[mxn+11],ed[mxn+11],cnt[mxn+11];
int mat[mxn+11][mxn+11],rq[mxn+11];

int main(){

    //freopen("in.txt","r",stdin);

    scanf("%d",&t);
    for(int ca=1;ca<=t;ca++){

        int ret=0;
        scanf("%d %d",&n,&m);
        for(int i = 1; i <=n;i++){
            scanf("%d %d %d",&st[i],&ed[i],&cnt[i]);
            int cur=cnt[i]/m;
            if(cnt[i]%m)cur++;
            rq[i]=cur;
            ret+=cur;
        }

        for(int i = 1; i<=n;i++){
            for(int j = 1; j <=n;j++){
                scanf("%d",&mat[i][j]);
            }
        }


        PushRelabel G = PushRelabel(2*n+3);
        source = 1;
        sink = 2*n+2;

        for(int i = 1;i<=n;i++){

            G.AddEdge(source,i+1,rq[i]);
            //cout<<"i:"<<i<<endl;
            for(int j = 1; j <=n;j++){
               // cout<<"\tj:"<<j<<"\tedi:"<<ed[i]<<"\tst[j]:"<<st[j]<<"\tij:"<<mat[i][j]<<endl;
                if(ed[i]+mat[i][j]<st[j]){
                    //cout<<"\t\ten\n";
                    G.AddEdge(i+1,j+n+1,rq[i]);
                }
            }

            G.AddEdge(1+n+i,sink,rq[i]);
           // cout<<"1+n+i:"<<1+n+i<<"\tsink:"<<sink<<endl;
        }

        ret-=G.GetMaxFlow(source,sink);

        printf("Case %d: %d\n",ca,ret);
    }

    return 0;
}
