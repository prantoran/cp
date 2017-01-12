//UVA 259 Software Allocation

#include<bits/stdc++.h>

using namespace std;

char ans[20];


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

string s;

int main(){

    #ifdef prantoran
        freopen("input.txt","r",stdin);
    #endif // prantoran

    int N1 = 1;
    int N2 = N1 + 10;
    int a,b,n,total,f;


    while(getline(cin,s)){
        PushRelabel G = PushRelabel(100);
        //2*n because the PushRelabel.addedge(u,v) does not add
        //(v,u) edge

        source = 0;
        sink =90;
        total = 0;

        do{
            a = N2+s[0]-'A';
            n = s[1]-'0';
            for(int i = 3;;i++){
                if(s[i]==';')break;
                b=N1+s[i]-'0';
                G.AddEdge(b,a,1); //adding directed edge (b,a)
            }
            G.AddEdge(a,sink,n);
            total+=n;

            getline(cin,s);
        }
        while(!s.empty());

        for(int i = 0 ; i<10;i++){
            G.AddEdge(source,i+N1,1);
        }
        int t2=G.GetMaxFlow(source,sink);

        if(G.GetMaxFlow(source,sink) == total){
            memset(ans,0,sizeof(ans));
            for(int i = N1;i<N1+10;i++){
                for(int j = 0,len = G.G[i].size(),v;j<len;j++){
                    v=G.G[i][j].to;
                    if(G.G[i][j].flow>0){
                        ans[i]=(char)(v-N2 + 'A');
                    }

                }
            }
            for(int i = 1;i<=10;i++){
                if(!ans[i])ans[i]='_';
            }
            for(int i =  1; i <=10;i++){
                cout<<ans[i];
            }cout<<"\n";
        }
        else{
            cout<<"!\n";
        }
    }
    return 0;
}
