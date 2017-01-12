//POJ 3321 Apple Tree
//http://poj.org/problem?id=3321
//Tag: Segment Tree on Tree
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const int mxn = 200011;
const int root = 1;
int n,timer,stt[mxn],fin[mxn];
int head[mxn],bro[mxn],vertex[mxn],edgeno;

void dfs(int node,int prv){

    stt[node]=timer++;

    for(int v,i = head[node];i;i=bro[i]){
        v=vertex[i];
        if(v==prv)continue;
        dfs(v,node);
    }

    fin[node]=timer++;
}

int tree[4*mxn];

void update(int node,int b,int e,int xx,int yy){

    if(e<xx || b>yy)return;
    if(xx<=b && e<=yy){
        tree[node]^=1;
        return;
    }
    int mid = (b+e)/2;
    int lc = node*2;
    int rc = lc|1;
    update(lc,b,mid,xx,yy);
    update(rc,mid+1,e,xx,yy);
    tree[node]=tree[lc]+tree[rc];
}

int query(int node,int b,int e,int xx,int yy){
    if(e<xx || b>yy)return 0;
    if(xx<=b && e<=yy)return tree[node];
    int mid = (b+e)/2;
    int lc = node*2;
    int rc = lc|1;
    return query(lc,b,mid,xx,yy)+query(rc,mid+1,e,xx,yy);
}

int main(){
    //freopen("in.txt","r",stdin);


    while(scanf("%d",&n)!=EOF){

        memset(head,0,sizeof(head));
        edgeno=1;
        for(int i = 1,u,v;i<n;i++){
            scanf("%d %d",&u,&v);

            bro[edgeno]=head[u];
            head[u]=edgeno;
            vertex[edgeno++]=v;

            bro[edgeno]=head[v];
            head[v]=edgeno;
            vertex[edgeno++]=u;


        }

        timer=1;
        dfs(root,0);
        timer--;

        memset(tree,0,sizeof(tree));
        for(int i =  1; i <=n;i++)update(1,1,timer,stt[i],stt[i]);
        char tp;
        int p,m;
        scanf("%d ",&m);
        while(m--){
            scanf("%c %d ",&tp,&p);
            if(tp=='C')update(1,1,timer,stt[p],stt[p]);
            else printf("%d\n",query(1,1,timer,stt[p],fin[p]));
        }
    }
    return 0;
}
