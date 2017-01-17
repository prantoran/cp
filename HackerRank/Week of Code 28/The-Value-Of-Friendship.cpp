/*
Contestant: prantoran
University: North South University
Motto     : Life is too short to wait
*/

#include<bits/stdc++.h>

#define LL long long 
#define PB push_back
#define PII pair<int,int>
#define FF first
#define SS second
#define MP make_pair 
#define INF (LL)1<<30
#define EPS 1e-9
#define PI 2*acos(0.0)
#define MOD 1000000007
#define MAXN 222222
using namespace std;


int t,n,m;
vector<int>G[MAXN];

int ca;
int vis[MAXN];


pair<LL,LL> bfs(int x){
    queue<int>Q;
    Q.push(x);
    vis[x]=ca;
    LL cnt = 1;
    LL sum = 0;


    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(auto v:G[u]){
            if(vis[v]==ca)continue;
            vis[v]=ca;
            Q.push(v);
            cnt ++;
            sum += (cnt)*(cnt-1);
        }
    }

    return MP(sum,cnt);


}

struct data{
    LL sum,cnt;
    data(LL _sum,LL _cnt):sum(_sum),cnt(_cnt){}
    data(pair<LL,LL> xx){
        sum = xx.FF;
        cnt = xx.SS;
    }
    data(){}

    bool operator<(const data aa)const{
        return cnt>aa.cnt;
    }
};

vector<data>b;


int main(){
    freopen("in.txt","r",stdin);
    //freopen("out2.txt","w",stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ca=0;
    memset(vis,0,sizeof(vis));
    cin>>t;
    while(t--){
        ca++;
        cin>>n>>m;
        for(int i = 0 ; i <=n;i++)G[i].clear();

        for(int i = 0,u,v ; i < m;i++){
            cin>>u>>v;
            G[u].PB(v);
            G[v].PB(u);
        }
        LL ans = 0;
        b.clear();
        for(int i = 1;i<=n;i++){
            if(vis[i]!=ca){
                pair<LL,LL> tmp = bfs(i);
                b.PB(tmp);
                ans += tmp.FF;
            }
        }
        sort(b.begin(),b.end());
        LL rem = 0;
        
        LL tot = 0;

        for(auto u:b){
            rem += (u.cnt - 1); // number of edge connections of each individual MST
            tot += (u.cnt)*(u.cnt - 1);
        }

        ans += tot * (m - rem); //adding redundant edges once all MSTs are connected

        for(auto u:b){
           // cout<<"u.cnt:"<<u.cnt<<endl;
            rem -= (u.cnt-1);
            ans += (u.cnt)*(u.cnt-1)*rem;
        }


        cout<<ans<<'\n';




    }
    

    return 0;
}