
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

const int mxn = 111;

int n , m, vis[mxn],turns,par[mxn];
ll cost[mxn][mxn],flow[mxn][mxn],dis[mxn];
ll cap[mxn][mxn],D,K,curflow,curcost,ans;
vi edges[mxn];

bool dijkstra(){
    for(int i = 0 ; i<=n;i++)dis[i]=inf;
    queue<int>q;
    bool inqueue[111]={0};
    q.push(0);
    inqueue[0]=1;
    dis[0]=0;
    while(!q.empty()){
        int u = q.front();
        inqueue[u]=0;
        q.pop();

        for(auto v:edges[u]){
            if(flow[v][u]>0 && dis[u]+(-cost[v][u])<dis[v]){//cancelling backward flow
                dis[v]=dis[u]+(-cost[v][u]);
                par[v]=u;
                if(!inqueue[v]){
                    inqueue[v]=1;
                    q.push(v);
                }
            }
            else if(cap[u][v]>flow[u][v] && dis[u]+cost[u][v]<dis[v]){
                dis[v]=dis[u]+cost[u][v];
                par[v]=u;
                if(!inqueue[v]){
                    inqueue[v]=1;
                    q.push(v);
                }
            }

        }
    }
    if(dis[n]==inf)return 0;
    return 1;
}

ll findminflow(int S,int T){
    ll bottleneck = inf;
    for(ll u = T;u!=S;u=par[u])
        bottleneck=min(bottleneck,cap[par[u]][u]-flow[par[u]][u]);
    return bottleneck;
}

void updateflow(int S,int T,int bottleneck){
    for(int u = T;u!=S;u=par[u]){
        flow[par[u]][u]+=bottleneck;
        flow[u][par[u]]-=bottleneck;
    }
}


ll MCMF(){
    ll mxflow=0;
    ll mncost=0;

    while(dijkstra()){
        ll ff = findminflow(0,n);
        updateflow(0,n,ff);
        mxflow+=ff;
        mncost+=(ff*dis[n]);
    }
    if(mxflow!=2)return -1;
    return mncost;
}


int main(){
    #ifdef prantoran

        freopen("input.txt","r",stdin);
    #endif // prantoran
   //ios_base::sync_with_stdio(false);

    while(cin>>n,n){
        cin>>m;
        memset(flow,0,sizeof flow);
        memset(cost,0,sizeof cost);
        memset(cap,0,sizeof cap);

        for(int i = 0 ; i<=n;i++){
            edges[i].clear();
        }
        for(int i = 0,u,v ; i< m;i++){
            cin>>u>>v;
            cin>>cost[u][v];
            cost[v][u]=cost[u][v];
            edges[u].pb(v);
            edges[v].pb(u);
        }



        for(int i = 0 ; i<=n;i++){
            for(auto j: edges[i]){
                cap[i][j]=1;
            }
        }

        edges[0].pb(1);
        cap[0][1]=2;

       /* for(int i = 0 ; i<=n;i++){
            for(int j = 0 ; j<=n;j++){
                cout<<cap[i][j]<<"\t";
            }cout<<"\n";
        }*/


        memset(vis,0,sizeof vis);
        ans=MCMF();
        if(ans==-1)cout<<"Back to jail\n";
        else cout<<ans<<"\n";

    }



    return 0;
}
