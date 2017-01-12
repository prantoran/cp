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

int n , m,par[mxn],src,des;
ll flow[mxn][mxn];
ll cost[mxn][mxn],curcost,ans,dis[mxn];
ll sum;
ll problemsize[69];

ll cap[mxn][mxn],curflow;
vi edges[mxn];

bool dijkstra(){
    for(int i = 0 ; i<=des;i++)dis[i]=inf;
    queue<int>q;
    bool inqueue[1111]={0};
    q.push(src);
    inqueue[src]=1;
    dis[src]=0;
    while(!q.empty()){
        int u = q.front();
        inqueue[u]=0;
        q.pop();

        for(auto v:edges[u]){
            if(flow[v][u]>0 && dis[u]+(-cost[v][u])  <dis[v]){//cancelling backward flow
                dis[v]=dis[u]+(-cost[v][u]);
                par[v]=u;
                if(!inqueue[v]){
                    inqueue[v]=1;
                    q.push(v);
                }
            }
            else if(cap[u][v]>flow[u][v] && dis[u]+cost[u][v]  <dis[v]){
                dis[v]=dis[u]+cost[u][v];
                par[v]=u;
                if(!inqueue[v]){
                    inqueue[v]=1;
                    q.push(v);
                }
            }

        }
    }
    if(dis[des]==inf)return 0;
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

        ll ff = findminflow(src,des);
        updateflow(src,des,ff);
        mxflow+=ff;
        mncost+=dis[des];



    }
    if(mxflow!=sum)return -1;
    return mncost;
}


int main(){
    #ifdef prantoran

        freopen("input.txt","r",stdin);
       // freopen("output.txt","w",stdout);
    #endif // prantoran
   //ios_base::sync_with_stdio(false);

    while(cin>>n>>m,n||m){

        memset(flow,0,sizeof flow);
        memset(cost,0,sizeof cost);
        memset(cap,0,sizeof cap);

        for(int i = 0 ; i<1111;i++){  //1111 nodes mcbm is psble because graph is sparse
            edges[i].clear();
        }
        sum=0;
        for(int i = 1 ; i<=n;i++){
            cin>>problemsize[i];
            sum+=problemsize[i];
        }

        for(int i = 1,cnt;i<=m;i++){
            cin>>cnt;
            for(int j = 0,v ; j<cnt;j++){
                cin>>v;
                edges[v].pb(i+n);
                edges[i+n].pb(v);

            }
        }

        for(int i = 1;i<=n;i++){ //considering only problem categories
            for(auto j:edges[i]){
                cap[i][j]=1;  //directed path/capacity
            }
        }

        for(int i = 1;i<=n;i++){
            edges[0].pb(i);
            edges[i].pb(0);
            cap[0][i]=problemsize[i];
        }

        src=0;
        des=n+m+1;

        for(int i = 1;i<=m;i++){
            edges[i+n].pb(des);
            edges[des].pb(i+n);
            cap[i+n][des]=1;  //Setting this 1 is imp for bpm, costed me a wa
        }

        ans=MCMF();

        if(ans==-1){
            cout<<"0\n";
        }
        else{
            cout<<"1\n";

            for(int i = 1;i<=n;i++){
                int cnt =0;
                for(int j = 1; j<=m;j++){
                    if(flow[i][j+n]==1){
                        cnt++;
                        if(cnt>1)cout<<" ";
                        cout<<j;
                    }//cout<<"cnt:"<<cnt;
                }cout<<"\n";
            }
        }
    }
    return 0;
}

