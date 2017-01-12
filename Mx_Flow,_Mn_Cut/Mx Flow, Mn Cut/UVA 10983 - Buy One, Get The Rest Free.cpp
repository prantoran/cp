//#define prantoran
//To Infinity And Beyond


#include<bits/stdc++.h>

#define sf scanf
#define pf printf
#define ll long long
#define inf 1<<30
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


struct debugger{
    template<typename T> debugger& operator, (const T& v){
        cerr<<v<<" ";
        return *this;
    }
}dbg;


#ifdef prantoran
    #include<ctime>
    clock_t tStart = clock();
   // freopen("input.txt","r",stdin);

    #define debug(args...){dbg,args; cerr<<endl;}
    #define timeStamp printf("Execution Time: %.2fs\n",(double)(clock()-tStart)/CLOCKS_PER_SEC);

#else
    #define debug(args...)
    #define timeStamp
#endif // prantoran


ll mod =1000000007;

ll mod_v(ll nn){return nn%mod;}

template<class T>
T fast_pow(T n , T p){
    if(p==0) return 1;
    if(p%2){
        T g=mod_v ( mod_v(n) * mod_v(fast_pow(n,p-1)) );
        return g;
    }
    else{
        T g=fast_pow(n,p/2);
        g=mod_v( mod_v(g) * mod_v(g) ) ;
        return g;
    }
}

template<class T>
inline T modInverse(T n){
    return fast_pow(n,mod-2);
}

//#####################^^prantoran^^##########################

const int mxn = 1111;

int pos[36][20];
int n,d,m;
int uu[mxn],vv[mxn],seats[mxn],cost[mxn],e[mxn];
int passSum,passengers[mxn];
vi allCost;
int source,sink;

int getPos(int city,int day){ return pos[city][day]; }


template<class TT>
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

    TT max_flow(int source, int sink){//Dinik's
        s = source; t = sink;
        TT f = 0,df;

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
};

flow_graph<int> G(mxn,2111111);

bool check(int limCost) {

    //build graph

    G.clear();

    for(int i = 0 ; i< m; i++ ) { // iterating through all flight path/edges
        if(cost[i]<=limCost){
            int u = getPos(uu[i],e[i]);
            int v = getPos(vv[i],e[i]+1); //arriving in morning of next day
            G.add_edge(u,v,seats[i]);

        }
    }
    //finished adding all valid edges whose cost is <= limCost

    for(int i = 1; i<=n;i++){
        for(int j = 0 ; j< d;j++ ) {
            int u = getPos(i,j);
            int v = getPos(i,j+1);
            G.add_edge(u,v,inf);
            //since people can stay in a city in ith day and (i+1)th day
        }
    }

    for(int i = 1; i<=n;i++){
        int v = getPos(i,0);
        G.add_edge(source,v,passengers[i]);
        //connecting source to each city on the first day
        //source -> {v,0}
    }

    int mf = G.max_flow(source,sink);

    return (mf == passSum);
}

int t,ca;

int main(){
    #ifdef prantoran

        freopen("input.txt","r",stdin);
       // freopen("output.txt","w",stdout);
    #endif // prantoran
   //ios_base::sync_with_stdio(false);

    for(int i = 0,pairid=0 ; i<33;i++){
        for(int j = 0 ; j<14;j++){
            pos[i][j]=++pairid;
        }
    }

    cin>>t;

    for(ca=1;ca<=t;ca++){
        set<int>setCost; //stores one copy of each unique cost in sorted order
        cin>>n>>d>>m;

        for(int i = 0 ; i<m;i++){
            cin>>uu[i]>>vv[i]>>seats[i]>>cost[i]>>e[i];
            setCost.insert(cost[i]);
        }

        passSum=0;
        for(int i =1;i<=n;i++){
            cin>>passengers[i];
            passSum+=passengers[i];
        }

        allCost.clear();
        for(auto it:setCost){
            allCost.pb(it);
        }
        //we are inserting all the values of setCost into allCost vector
        //to facilitate binary search
        source=getPos(0,0); //super_sourcenode=0, day=0
        sink=getPos(n,d); //final node=n,final day = d

        int lo = 0, hi = allCost.size() - 1, ans = inf;
        while(lo<=hi){ //binary search on sorted costs of planes
            int mid = (hi+lo)/2;

            if(check(allCost[mid])){
                ans=min(ans,allCost[mid]);
                hi=mid-1;
            }
            else{
                lo=mid+1;
            }
        }
        cout<<"Case #"<<ca<<": ";
        if(ans == inf ){
            cout<<"Impossible\n";
        }
        else{
            cout<<ans<<"\n";
        }
    }
    return 0;
}
