#include<bits/stdc++.h>

#define FF   first 
#define SS   second
#define PB   push_back
#define MP   make_pair
#define LL   long long
#define PI   2*acos(0.0)
#define EPS  1e-9
#define INF  (LL)1<<60
#define PII  pair<int,int>
#define PLL  pair<LL,LL> 
#define MAXN 211111

using namespace std;
LL a[MAXN];

struct SegmentTree{
    int l,r;
    LL mx,mn,mxd;
    SegmentTree *lc,*rc;
    SegmentTree(){
        mx = -INF;
        mn = INF;
        mxd = -INF;
    }
    SegmentTree(SegmentTree *_lc,SegmentTree *_rc):lc(_lc),rc(_rc){
        if(!lc && !rc)return;
        l = lc->l;
        r = rc->r;
        mx = max(lc->mx,rc->mx);
        mn = min(lc->mn,rc->mn);
        mxd = max(max(rc->mxd,lc->mxd),rc->mx-lc->mn);
    }
    void UpdateNode(){
        if(!lc && !rc)return;
        
        mx = max(lc->mx,rc->mx);
        mn = min(lc->mn,rc->mn);
        mxd = max(max(rc->mxd,lc->mxd),rc->mx-lc->mn); 
    }
};

SegmentTree * BuildTree(int l,int r){
    if(l==r){
        SegmentTree *tree = new SegmentTree();
        tree->l = tree->r = l;
        tree->lc = tree->rc = NULL;
        tree->mx = tree->mn = a[l];
        tree->mxd = 0;
        return tree;
    }else{
        int m = (l+r)>>1;
        return new SegmentTree(BuildTree(l,m),BuildTree(m+1,r));
    }
}

void UpdateTree(SegmentTree * tree,int idx,LL val){
    if(tree->l == tree->r){
        tree->mn = tree->mx =  val;
        tree->mxd = 0;
    }else{
        int m = (tree->l+tree->r)>>1;
        if(idx<=m){
            UpdateTree(tree->lc,idx,val);
        }else{
            UpdateTree(tree->rc,idx,val);
        }
        tree->UpdateNode();
    }
}

SegmentTree * QueryTree(SegmentTree * tree,int l,int r){
    if(l>r)return new SegmentTree();
    if(tree->l == l && tree->r == r){
        return tree;
    }else{
        int m = (tree->l+tree->r)>>1;
        return new SegmentTree(QueryTree(tree->lc,l,min(m,r)),QueryTree(tree->rc,max(m+1,l),r));
    }
}

int main(){
    //freopen("in.txt","r",stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t,n,q,tp,l,r;
    LL val;
    cin>>t;
    for(int ca=1;ca<=t;ca++){
        cin>>n>>q;
        for(int i = 1;i<=n;i++)cin>>a[i];
        SegmentTree * root = BuildTree(1,n);
        cout<<"Case "<<ca<<":\n";
        while(q--){
            cin>>tp>>l;
            if(tp==1){
                cin>>val;
                UpdateTree(root,l,val);
            }else{
                cin>>r;
                SegmentTree *cur = QueryTree(root,l,r);
                cout<<cur->mxd<<"\n";
            }
        }
    }
    return 0;
}