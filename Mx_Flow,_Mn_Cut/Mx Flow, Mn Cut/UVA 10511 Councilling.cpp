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

int t,n1,n2,n3,p[mxn],source,sink;
vi L[mxn];
string personName[mxn],clubName[mxn];
map<string,int>partyID,clubID;
string line,name,party,club;

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
}G(10000+2,8000+38000+1000+1000);

int main(){
    #ifdef prantoran

        freopen("input.txt","r",stdin);
       // freopen("output.txt","w",stdout);
    #endif // prantoran
   //ios_base::sync_with_stdio(false);

    bool first=1;

    cin>>t;

    getline(cin,line);
    getline(cin,line);

    while(t--){
        n1=0,n2=0,n3=0;
        //n1=no. of residents
        //n2=no. of parties
        //n3=no. of clubs

        partyID.clear();
        clubID.clear();
        G.clear();

        while(getline(cin,line)){
            if(line.empty())break;

            istringstream is(line);

            is>>name>>party;
            personName[n1]=name;

            if(partyID.find(party)==partyID.end()){
                partyID[party]=n2++;
            }

            p[n1]=partyID[party];
            //cout<<"n1:"<<n1<<"\tpid:"<<p[n1]<<"\tclub:"<<endl;
            while(is>>club){
                if(clubID.find(club)==clubID.end()){
                    clubID[club]=n3;
                    clubName[n3]=club;
                    n3++;
                }
                L[n1].pb(clubID[club]);
                //cout<<clubID[club]<<" ";
            }//cout<<endl;
            n1++;
        }

        source = 0;
        sink = 1+n1+n2+n3;
        //n1=no. of residents
        //n2=no. of parties
        //n3=no. of clubs

        for(int i = 0;i<n3;i++)G.add_edge(source, 1+i,1); //directed edge with cap 1
        for(int i = 0;i<n1;i++)G.add_edge(1+n3+i,1+n3+n1+p[i],1);
        //directed edge from resident (1+n3+(i)) to party (1+n3+n1+(p[i]))
        for(int i = 0;i<n2;i++)G.add_edge(1+n1+n3+i,sink,(n3-1)/2);
        //directed edge from party (1+n3+n1+(i)) to sink

        //mapping: <source><clubs>residents><parties><sink>

        for(int i = 0 ; i<n1;i++){
            for(auto v:L[i]){
                G.add_edge(1+v,1+n3+i,1);
                //0 is source
                //directed edge from from club v to resident i
            }
        }

        if(!first)cout<<"\n";
        first = 0;

        if(G.max_flow(source,sink)!=n3) cout<<"Impossible.\n";
        else{
            int E = G.E;
            for(int e = 0 ; e < E; e+= 2){ //iterating over all front edges
                int u = G.to[e^1]-1, v = G.to[e]-1-n3;
                //since u,v is remapped to 0 by subtracting 1 from u and
                //(1+n3) from v, u==0 represents the first club
                if(u>=n3)continue;
                //u<n3 == club nodes
                if(v>=n1)continue;
                //n3<v<n1 == resident nodes
                if(v<0 || u<0)continue;
                //v<0 == v=source || u<0 == u=source
                if(G.cap[e]==0){
                    //initially u-v's cap is 1
                    //if used then cap ==0
                    cout<<personName[v]<<" "<<clubName[u]<<"\n";
                }
            }
        }

        for(int i = 0 ; i<n1;i++)L[i].clear(); //clearing resident to clubs edges

    }

    return 0;
}
