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

#define eps 0.000001

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

int n , m,par[mxn],src,des;
ll flow[mxn][mxn];
double cost[mxn][mxn],curcost,ans,dis[mxn];

ll cap[mxn][mxn],curflow;
vi edges[mxn];

bool dijkstra(){
    for(int i = 0 ; i<=des;i++)dis[i]=inf;
    queue<int>q;
    bool inqueue[111]={0};
    q.push(src);
    inqueue[src]=1;
    dis[src]=0;
    while(!q.empty()){
        int u = q.front();
        inqueue[u]=0;
        q.pop();

        for(auto v:edges[u]){
            if(flow[v][u]>0 && dis[u]+(-cost[v][u]) +eps <dis[v]){//cancelling backward flow
                dis[v]=dis[u]+(-cost[v][u]);
                par[v]=u;
                if(!inqueue[v]){
                    inqueue[v]=1;
                    q.push(v);
                }
            }
            else if(cap[u][v]>flow[u][v] && dis[u]+cost[u][v] + eps <dis[v]){
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


double MCMF(){
    ll mxflow=0;
    double mncost=0;

    while(dijkstra()){

        ll ff = findminflow(src,des);
        //cout<<"\tff:"<<ff<<endl;
        updateflow(src,des,ff);
        mxflow+=ff;
        mncost+=dis[des];



    }
    //cout<<"mxflw:"<<mxflow<<endl;
    if(mxflow!=n)return -1;
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

        for(int i = 0 ; i<100;i++){
            edges[i].clear();
        }

        for(int i = 1 ; i<=n;i++){
            for(int j = 1 ; j<=m;j++){
                cin>>cost[i][j+n];
                cost[j+n][i]=cost[i][j+n];
                edges[i].pb(j+n);
                edges[j+n].pb(i);
            }
        }


        for(int i = 1 ; i<=n;i++){
            for(auto j: edges[i]){
                cap[i][j]=1;
            }
        }

        for(int i = 1;i<=n;i++){
            cost[0][i]=0;
            cost[i][0]=0;
            cap[0][i]=1;
            edges[0].pb(i);
        }

        src=n+m+1;
        des=src+1;

        cost[src][0]=0;
        cost[0][src]=0;
        edges[src].pb(0);
        cap[src][0]=n;

        for(int i=1;i<=m;i++){
            cost[i+n][des]=0;
            cost[des][i+n]=0;
            cap[i+n][des]=1;
            edges[i+n].pb(des);
        }
       /* for(int i = 0 ; i<=n;i++){
            for(int j = 0 ; j<=n;j++){
                cout<<cap[i][j]<<"\t";
            }cout<<"\n";
        }*/





        ans=MCMF();
        ans/=n;
        ans=(ans*100+0.01)/100;
       // ans+=(double)0.005;
        pf("%.2f\n",ans);
        //cout<<setprecision(2)<<fixed<<ans<<"\n";
    }



    return 0;
}

