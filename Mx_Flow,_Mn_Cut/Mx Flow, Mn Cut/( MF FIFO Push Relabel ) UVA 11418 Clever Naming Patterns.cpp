
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

int t,ca,n;
string word;
map<int,string>idname;
vector<string> ans;

int main(){

    #ifdef prantoran
        freopen("input.txt","r",stdin);
    #endif // prantoran
    
    /*
    source = 0
    1-26 problems
    
    26 - 26*26 + 26
    30-800 words
    
    805 - 840 chars
    
    sink = 900
    
    */
    int source= 0 , sink = 900;
    int wordStart = 30;
    int letterStart = 805;
    
   
   
    cin>>t;
    for(ca=1;ca<=t;ca++){
        
        PushRelabel G = PushRelabel(1000);
        idname.clear();
        
        int wordid= wordStart;
        
        cin>>n;
        //cout<<"n:"<<n<<endl;
        for(int i = 1,k;i<=n;i++){
            cin>>k;
            //cout<<"\tk:"<<k<<endl;
            G.AddEdge(source,i,1);
            for(int j = 1;j<=k;j++){
               cin>>word; 
               
               for(int p = 0 , len = word.length();p<len;p++){
                    word[p]=tolower(word[p]);
               }
               
               //cout<<"\t\tword:"<<word<<endl;
               
               int id = word[0]-'a';
               
               if(id>=n)continue;
               
               idname[wordid]=word;
               G.AddEdge(i,wordid,1);
               
               G.AddEdge(wordid,letterStart+id,1);
               G.AddEdge(letterStart+id,wordid,1);
               wordid++;
                
            }
            //G.AddEdge(letter+i,sink,1);
        }
        for(int i = 0 ; i < 26;i++){
            G.AddEdge(letterStart+i,sink,1);
        }
        //cout<<"pss\n";
        
        
        ans.clear();
        
        if(G.GetMaxFlow(source,sink)){
            //cout<<"mxflow:"<<G.GetMaxFlow(source,sink)<<"\n";
            for(int i = 1;i<=n;i++){
            
                int len = G.G[i].size();
                //cout<<"i:"<<i<<"\tlen:"<<len<<endl;
                for(int j = 0 , v ; j<len;j++){
                    //cout<<"\tj:"<<j<<endl;
                    if(G.G[i][j].flow>0){
                        int v = G.G[i][j].to;
                        //cout<<"\t\tv:"<<v<<endl;
                        string tmp=idname[v];
                        
                            tmp[0]-='a';
                            tmp[0]+='A';
                        
                        //cout<<"\t\t\ttmp:"<<tmp<<endl;
                        ans.push_back(tmp);
                    }
                }
            }
        }
        sort(ans.begin(),ans.end());
        cout<<"Case #"<<ca<<":\n";
        for(auto v:ans){
            cout<<v<<"\n";
        }
    }
    

    return 0;
}
