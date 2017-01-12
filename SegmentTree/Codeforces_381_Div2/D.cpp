//http://codeforces.com/contest/740/problem/D
//dynamic segment tree
#include<bits/stdc++.h>

#define LL long long 
#define MAXN 211111
#define MP make_pair
#define FF first 
#define SS second 
#define PB push_back
#define ALL(x) (x).begin(),(x).end()

using namespace std;

int n;
LL a[MAXN];

vector< pair<int,LL> > G[MAXN];

int st[MAXN],cc,sz[MAXN],en[MAXN];
LL b[MAXN], d[MAXN];

void dfs(int u, LL _dist){
    st[u] = ++cc;
    sz[u] = 1;
    b[cc] = _dist - a[u];
    d[u] = _dist;
    for(auto x:G[u]){
        dfs(x.FF,_dist+x.SS);
        sz[u] += sz[x.FF];
    }
    en[u] = cc;
    return;
}

struct SegmentTree{
    int l,r;
    SegmentTree *lc,*rc;
    vector<LL> box;
    SegmentTree(){}
    SegmentTree(SegmentTree *_lc,SegmentTree *_rc):lc(_lc),rc(_rc){
        l = lc->l;
        r = rc->r;
        box.resize((int)lc->box.size() + rc->box.size());
        merge(lc->box.begin(),lc->box.end(),
            rc->box.begin(),rc->box.end(),box.begin());
    }
};

SegmentTree * BuildTree(int l,int r){
    if(l==r){
        SegmentTree * tree = new SegmentTree();
        tree->l = tree->r = l;
        tree->lc = tree->rc = NULL;
        tree->box.PB(b[l]);
        return tree;
    }else{
        int mid = (l+r)>>1;
        return new SegmentTree(
            BuildTree(l,mid),BuildTree(mid+1,r));
    }
}

LL QueryTree(SegmentTree* tree,int l,int r,LL val){
    if(l>r)return 0;
    if(tree->l == l && tree->r == r){
        LL ret = tree->box.end() - upper_bound(ALL(tree->box),val);
        return ret;
    }
    int mid = (tree->l+tree->r)>>1;
    return QueryTree(tree->lc,l,min(r,mid),val)
        +QueryTree(tree->rc,max(mid+1,l),r,val);
}

int main(){
    freopen("in.txt","r",stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i = 1;i<=n;i++){
        cin>>a[i];
        G[i].clear();
    }
    for(int i = 2,u,w;i<=n;i++){
        cin>>u>>w;
        G[u].PB(MP(i,w));
    }
    cc = 0;
    dfs(1,0); //1 is the root
    SegmentTree * tree = BuildTree(1,n);

    for(int i = 1;i<=n;i++){
        if(i!=1)cout<<" ";
        LL val = d[i];
        LL res = QueryTree(tree,st[i],en[i],val);
        res = sz[i] - res - 1;
        cout<<res;
    }cout<<"\n";
    return 0;
}