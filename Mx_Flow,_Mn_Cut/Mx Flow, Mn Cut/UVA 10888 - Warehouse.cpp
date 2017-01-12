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

const ll mxn = 2222;
const ll INF = 1e9;
typedef pair<int,ll>PII;
ll offset = 100000;
int N1,N2;
//N1==1st bipartite set size
//N2=2nd ,, ,,
vector<PII> edges[mxn]; // different from the usual pii
//int indicates that the array deals with node to node relations
//ll indicates the values for each node that we are interested in
ll praw[mxn];
ll aa[mxn];
ll bb[mxn];
int ni2[mxn];// The node in M1 that is matched to a M2; -1 if unmatched
ll slack[mxn];
int va[mxn]; //used for marking nodes in N1 for each find() call
int vb[mxn];

bool find(int p){
  //  cout<<"\tp:"<<p<<"\tva["<<p<<"]:"<<va[p]<<endl;
    if( va[p] ) return 0;
    va[p] = 1;
    for( PII cur: edges[p] ) {
        int q = cur.ff; // a node from the set N2
        if( !vb[q] && aa[p] + bb[q] == cur.ss ) {
            vb[q]=1;
            if( ni2[q]==-1 || find(ni2[q])){
                //either q was not taken before or
                //a valid augmenting path is found excluding q
                praw[p]=cur.ss; ni2[q]=p;return 1;
            }
        }
        slack[q]=min(slack[q],aa[p]+bb[q]-cur.ss);
    }
    return 0;
}

//we are doing the dual problem of finding max cost bpm
//then use that to find mincost bpm? huh?!
ll km(){
    memset(bb,0,sizeof bb);
    memset(praw,0,sizeof praw);
    memset(ni2,-1,sizeof ni2);

    for(int i = 0 ; i < N1;i++){
        aa[i]=-INF;
        for(PII cur:edges[i])
            aa[i]=max(aa[i],cur.ss); //second element has cost
    }

    for(int x = 0 ; x < N1; x++ ) { //we are trying to match elements in set N1
 //cout<<"x:"<<x<<endl;
        while(1){
           //
            memset(va,0,sizeof va);
            memset(vb,0,sizeof vb);
            for(int j = 0 ; j < N2;j++)slack[j]=INF;
            if(find(x))break; // a match has been found
            ll d = INF;
            for(int j = 0 ; j < N2;j++ ) {
                if(!vb[j] && slack[j]<d )d = slack[j];
            }
            for(int i = 0 ; i < N1;i++ ) if(va[i]) aa[i] -= d;
            for(int j = 0 ; j < N2;j++ ) {
                if( vb[j] ) bb[j] += d;
                else slack[j] -= d;
            }
        }
    }
    ll ans = 0;
    for(int i = 0 ; i < N1;i++ ) ans += ( offset - praw[i]);
    return ans;
}

int t,n,m;
char grid[60][60];
int dist[60][60];

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};



int main(){
    #ifdef prantoran

        freopen("input.txt","r",stdin);
       // freopen("output.txt","w",stdout);
    #endif // prantoran
   //ios_base::sync_with_stdio(false);

    //cin>>t;
    sf("%d",&t);
    while(t--){
        for(int i = 0 ; i < mxn;i++)edges[i].clear();
        //cin>>n>>m;
        sf("%d %d ",&n,&m);
//        for(int i = 0 ; i <n;i++)cin>>grid[i];
        for(int i = 0 ; i <n;i++)sf("%s",&grid[i]);

       // cout<<"n:"<<n<<"\tm:"<<m<<endl;
       // for(int i = 0 ; i < n ; i++ ) {
       //     cout<<grid[i];cout<<endl;
       // }cout<<endl;

        N1=0;
        for(int i = 0 ; i < n;i++){
            for(int j =  0 ; j < m ; j++ ) {
                if(grid[i][j]=='B'){
                    memset(dist,-1,sizeof dist);
                    queue<pii>q;q.push({i,j});
                    dist[i][j]=0;
                    while(!q.empty()){
                        int y = q.front().ff, x = q.front().ss;
                        q.pop();
                        for(int k = 0 ; k< 4;k++){
                            int nx = x + dx[k];
                            int ny = y + dy[k];

                            if(nx<0 || nx>=m || ny < 0 || ny>=n ||
                                    dist[ny][nx]!=-1 || grid[ny][nx]=='#')continue;
                            dist[ny][nx]=dist[y][x]+1;
                            q.push({ny,nx});
                        }
                    }
                    N2=0;
                    for(int y = 0 ; y<n;y++){
                        for(int x = 0 ; x < m;x++){
                            if(grid[y][x]=='X'){
                                if(dist[y][x]>=0){
                                    edges[N1].pb({N2,offset-dist[y][x]});
                                }
                                N2++;
                            }
                        }
                    }
                    N1++;
                }
            }
        }
        cout<<km()<<"\n";
        //pf("%d\n",km());
    }


    return 0;
}
