#include<bits/stdc++.h>
#define mxn 11111
#define LN 14
#define root 1
using namespace std;

int t,n,ptr;
vector<pair<int,int> >adj[mxn];
string tp;
int pa[LN][mxn];
vector<int> ind[mxn];

int chainNo;
int d[mxn],h[mxn];
int subsize[mxn];
int chainHead[mxn],posInBase[mxn],chainInd[mxn];
int otherEnd[mxn];

int baseArray[mxn];

//-------------------------------------------
int tree[mxn*4];



//-------------------------------------------

void dfs(int u,int prev,int _h){
    pa[0][u]=prev;
    h[u]=_h;
    subsize[u]=1;
    int i = 0;
    for(auto cp:adj[u]){
        if(cp.first!=prev){
          otherEnd[ind[u][i]]=cp.first;
          i++;
          d[cp.first]=d[u]+cp.second;
          dfs(cp.first,u,_h+1);
          subsize[u]+=subsize[cp.first];
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

int queryTree(int u,int b,int e,int xx,int yy){
  if(b>yy || e<xx)return 0;
  if(xx<=b && e<=yy)return tree[u];
  int lc = u*2;
  int rc = lc|1;
  int mid = (b+e)/2;
  return queryTree(lc,b,mid,xx,yy)+queryTree(rc,mid+1,e,xx,yy);
}

int query_up(int u,int v){
  if(u==v)return 0;
  int uchain,vchain = chainInd[v],ans=0;
  while(1){
    uchain = chainInd[u];
    if(uchain == vchain){
      if(u==v)break;
      ans +=queryTree(1,0,ptr-1,posInBase[v]+1,posInBase[u]);
      break;
    }
    ans+=queryTree(1,0,ptr-1,posInBase[chainHead[uchain]],posInBase[u]);
    u = chainHead[uchain];
    u = pa[0][u];
  }
}

//-------------------------------------------

int query(int u,int v){
  int lca= LCA(u,v);
  int ans = query_up(u,lca);
  ans +=query_up(v,lca);
}

//---------------------------------------------

void build(int u,int b,int e){
  if(b==e){
    tree[u]=baseArray[b];
    return;
  }
  int lc = u*2;
  int rc = lc|1;
  int mid = (b+e)/2;
  build(lc,b,mid);
  build(rc,mid+1,e);
  tree[u]=tree[lc]+tree[rc];
}


//----------------------------------------

void HLD(int u,int prev,int cost){
  if(chainHead[chainNo]==-1)
    chainHead[chainNo]=u;
  chainInd[u]=chainNo;
  posInBase[u]=ptr;
  baseArray[ptr++]=cost;

  int sc = -1,ncost;
  for(auto v:adj[u]){
      if(v.first!=prev){
        if(sc==-1 || subsize[v.first]>subsize[sc]){
          sc=v.first;
          ncost = v.second;
        }
      }
  }
  if(sc!=-1)HLD(sc,u,ncost);
  for(auto v:adj[u]){
    if(v.first!=sc && v.first!=prev){
      chainNo++;
      HLD(v.first,u,v.second);
    }
  }
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
    //freopen("in.txt","r",stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>t;
    while(t--){
      ptr=0;
        cin>>n;
       // cout<<"n:"<<n<<endl;
        for(int i = 0 ; i <=n;i++){
            adj[i].clear();
            ind[i].clear();
            chainHead[i]=-1;
            ind[i].clear();
        }
        memset(pa,0,sizeof(pa));
        
        for(int i = 1,u,v,c ;i <n;i++){
            cin>>u>>v>>c;
            adj[u].push_back({v,c});
            adj[v].push_back({u,c});
            ind[u].push_back(i);
            ind[v].push_back(i);
        }
        d[root]=0;
        dfs(root,-1,0);
        HLD(root,-1,-1);
        build(1,0,ptr-1);
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
                //if(lca == u || lca == v ) ans = abs(d[u]-d[v]);
                //else ans = d[u]+d[v]-2*d[lca];
                ans = query(u,v);
            }
            cout<<ans<<"\n";
        }
    }
    return 0;
}