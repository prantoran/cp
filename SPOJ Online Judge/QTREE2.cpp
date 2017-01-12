#include<bits/stdc++.h>
#define mxn 11111
#define LN 14
#define root 1
using namespace std;

int t,n;
vector<pair<int,int> >adj[mxn];
string tp;
int pa[LN][mxn];
//-------------------------------------------
int d[mxn],h[mxn];

void dfs(int u,int prev){
    pa[0][u]=prev;
    for(auto cp:adj[u]){
        if(cp.first!=prev){
            d[cp.first]=d[u]+cp.second;
            h[cp.first]=h[u]+1;
            dfs(cp.first,u);
        }
    }
}
//--------------------------------------------

int LCA(int u,int v){
    if(h[u]<h[v])swap(u,v);
    int diff = h[u]-h[v];
    for(int i = 0 ; i < LN;i++)if( (diff>>i)&1 ) u = pa[i][u];
    if(u==v)return u;
    for(int i = LN-1;i>=0;i--)
        if(pa[i][u]!=pa[i][v]){
            u = pa[i][u];
            v = pa[i][v];
        }    
    return pa[0][u];
}

//--------------------------------------------

int getKth(int u,int v,int lca,int k){
    int nodes;
    if(lca == u){
        //cout<<"\ten\n";
        nodes = h[v]-h[u]+1; //end point inclusive
        swap(u,v);
        k = nodes - k;
    
    }
    else if(lca == v){ 
       k--;
    }
    else{
        if(h[u]-h[lca]+1 <k){
            nodes = h[u]+h[v] -2*h[lca] +1;
            k = nodes - k;
            swap(u,v);
        }
        else{
            k--;
        }
    }
    for(int i = 0;i<LN;i++){
        if((k>>i)&1){
            u = pa[i][u];
        }
    }
    return u;
}

//--------------------------------------------

int main(){
    freopen("in.txt","r",stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>t;
    while(t--){
        cin>>n;
        for(int i = 0 ; i <=n;i++)adj[i].clear();

        for(int i = 1,u,v,c ;i <n;i++){
            cin>>u>>v>>c;
            adj[u].push_back({v,c});
            adj[v].push_back({u,c});
        }
        d[root]=0;
        h[root]=0;
        memset(pa,0,sizeof(pa));
        dfs(root,-1);

        // Below Dynamic programming code is for LCA. [rmq]
       
        for(int i = 1;i<LN;i++){
            for(int j = 1 ; j <=n;j++){
                if(pa[i-1][j]!=-1){ //parent of dis 2^(i-1) defined
                    pa[i][j]=pa[i-1][pa[i-1][j]];
                }
            }
        }

        while(cin>>tp){
            if(tp[1]=='O')break;
            int u , v, k, ans;
            cin>>u>>v;
            int lca = LCA(u,v);
            if(tp[0]=='K'){
                cin>>k;
                ans = getKth(u,v,lca,k);
            }
            else{
                if(lca == u || lca == v ) ans = abs(d[u]-d[v]);
                else ans = d[u]+d[v]-2*d[lca];
            }
            cout<<ans<<"\n";
        }
    }
    return 0;
}