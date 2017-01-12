#include<bits/stdc++.h>
#define ll long long 
#define mxn 555555
using namespace std;
/*** FAST I/O ***/

//#define gc getchar
#define gc getchar_unlocked

void readInt(int &x){
    register char c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}
/*** FAST I/O Ends ***/

struct Edge {
    bool open;
    ll x, yMin, yMax;
    Edge(int x, int y1, int y2, bool op) {
        this->x = x;
        yMin = y1, yMax = y2;
        open = op;
    }
    bool operator < (const Edge &e) const {
        return (x < e.x);
    }
};

vector<Edge> edges;
int t,n,ca,m;
ll h[mxn];

ll tree[mxn];
int counter[mxn];

void update(int node,int l,int r,ll ymin,ll ymax,bool open){
    if(h[r]<ymin || h[l]>ymax)return;
    int lc = node<<1 , mid = (l+r)>>1;
    if(ymin <=h[l] && h[r] <= ymax){
        counter[node] += open? 1:-1;
        if(counter[node])tree[node]=h[r]-h[l];
        else tree[node]=tree[lc] + tree[lc+1];
        return;
    }
    if(l+1>=r)return;
    if(h[mid]>ymin)update(lc,l,mid,ymin,ymax,open);
    if(h[mid]<ymax)update(lc|1,mid,r,ymin,ymax,open);
    if(counter[node])tree[node]=h[r]-h[l];
    else tree[node]=tree[lc] + tree[lc+1];
}

int main(){
    freopen("in.txt","r",stdin);
    readInt(t);
    for(ca=1;ca<=t;ca++){
        readInt(n);
        edges.clear();
        m = 0;
        for(int i = 0,x1,x2,y1,y2 ; i < n;i++){
            readInt(x1);readInt(y1);readInt(x2);readInt(y2);
            edges.push_back(Edge(x1,y1,y2,1));
            edges.push_back(Edge(x2,y1,y2,0));
            h[++m]=y1;
            h[++m]=y2;
        }

        sort(h+1,h+m+1);
        int k = 1;
        for(int i = 2;i<=m;i++)if(h[k]!=h[i])h[++k]=h[i];
        m = k;
        //for(int i = 1;i<=m;i++)cout<<"h["<<i<<"]:"<<h[i]<<endl;
        memset(tree,0,sizeof(tree));
        memset(counter,0,sizeof(counter));
        sort(edges.begin(),edges.end());
        update(1,1,m,edges[0].yMin,edges[0].yMax,edges[0].open);
        ll ans = 0;
        int len = edges.size()-1;
        for(int i = 1;i<len;i++){
            ans += tree[1]*(edges[i].x - edges[i-1].x);
            update(1,1,m,edges[i].yMin,edges[i].yMax,edges[i].open);
        }
        ans+=tree[1]*(edges[len].x-edges[len-1].x);
        printf("Case %d: %lld\n",ca,ans);
    }
    return 0;
}