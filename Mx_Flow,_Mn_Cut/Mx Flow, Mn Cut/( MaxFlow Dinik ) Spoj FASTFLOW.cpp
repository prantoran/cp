//SPOJ FASTFLOW
//Algo: Dinik

//#define prantoran
//To Infinity And Beyond


#include<bits/stdc++.h>

#define sf scanf
#define pf printf
#define ll long long
#define inf (ll)1<<60
#define sz 2111111
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define ff first
#define ss second
#define vi vector<int>

#define vl vector<ll>
#define pb push_back
#define pdd pair<double,double>
#define pll pair<ll,ll>
#define lazy second

#define uu first
#define vv second
#define vii vector< pair<int,int> >
#define vi vector<int>
#define vll vector<ll>


using namespace std;

struct flow_graph{
    int MAX_V,E,s,t,head,tail;
    int *cap,*to,*next,*last,*dist,*q,*now; //pointers
    //last == fin , VIP, lsat[u] indicates first edge from node u
    //next and last stores edge ids/no.

    flow_graph(){}

    flow_graph(int V, int MAX_E){
        MAX_V = V; E = 0;
        cap = new int[2*MAX_E], to = new int[2*MAX_E], next = new int[2*MAX_E];
        last = new int[MAX_V], q = new int[MAX_V];
        dist = new int[MAX_V], now = new int[MAX_V];
        fill(last,last+MAX_V,-1);
    }

    void clear(){
        fill(last,last+MAX_V,-1);
        E = 0;
    }

    void add_edge(int u, int v, int uv, int vu = 0){
        //u = src, v = des, uv = u-v path cap, vu = v-u path cap
        //e=even : stores front edge
        //e=odd : stores back edge
        //^ operator toggles between front and back edges
        to[E] = v, cap[E] = uv, next[E] = last[u]; last[u] = E++;
        to[E] = u, cap[E] = vu, next[E] = last[v]; last[v] = E++;
    }

    bool bfs(){
        fill(dist,dist+MAX_V,-1);
        head = tail = 0;

        q[tail] = t; ++tail;
        dist[t] = 0;

        while(head<tail){
            int v = q[head]; ++head;

            for(int e = last[v];e!=-1;e = next[e]){
                if(cap[e^1]>0 && dist[to[e]]==-1){
                    q[tail] = to[e]; ++tail;
                    dist[to[e]] = dist[v]+1;
                }
            }
        }

        return dist[s]!=-1;
    }

    int dfs(int v, int f){
        if(v==t) return f;

        for(int &e = now[v];e!=-1;e = next[e]){
            if(cap[e]>0 && dist[to[e]]==dist[v]-1){
                int ret = dfs(to[e],min(f,cap[e]));

                if(ret>0){
                    cap[e] -= ret;
                    cap[e^1] += ret;
                    return ret;
                }
            }
        }

        return 0;
    }

    long long max_flow(int source, int sink){//Dinik's
        s = source; t = sink;
        long long f = 0,df;

        while(bfs()){
            for(int i = 0;i<MAX_V;++i) now[i] = last[i];

            while(true){
                df = dfs(s,INT_MAX);
                if(df==0) break;
                f += df;
            }
        }

        return f;
    }
}G(6666,33333);


int N , M;

int main(){
    #ifdef prantoran

        freopen("input.txt","r",stdin);
       // freopen("output.txt","w",stdout);
    #endif // prantoran
   //ios_base::sync_with_stdio(false);

    sf("%d %d",&N,&M);

    G.clear();


    for(int i = 0 , u , v , c ; i < M ; i++ ) {
        sf("%d %d %d",&u,&v,&c);
        G.add_edge(u,v,c,c);
    }
    cout<<G.max_flow(1,N)<<"\n";

    return 0;
}

