#include<bits/stdc++.h>
using namespace std;

const int mxn = 696;
const int mxn2= 1111111;

int n , m;
char maze[mxn][mxn];
int col,color[mxn][mxn];

int mi[4]={0,0,1,-1};
int mj[4]={1,-1,0,0};
int di[4]={1,1,-1,-1};
int dj[4]={-1,1,-1,1};



bool valid(int p,int q,int RR,int CC){
    if(p<0 ||p>=RR || q<0 || q>=CC)return 0;
    return 1;
}

void bfs(int pp,int qq){
    queue< pair<int,int> > q;
    q.push({pp,qq});
    color[pp][qq]=col;
    while(!q.empty()){
        pair<int,int> cur = q.front();
        q.pop();
        for(int i = 0 ; i < 4;i++){
            int ni = cur.first + mi[i];
            int nj = cur.second + mj[i];
            if(valid(ni,nj,n,m) && color[ni][nj]==0 && maze[ni][nj]=='#'){
                color[ni][nj]=col;
                q.push({ni,nj});
            }
        }
        for(int i = 0 ; i < 4;i++){
            int ni = cur.first + di[i];
            int nj = cur.second + dj[i];
            if(valid(ni,nj,n,m) && color[ni][nj]==0 && maze[ni][nj]=='#'){
                color[ni][nj]=col;
                q.push({ni,nj});
            }
        }
    }
}

vector<pair<int, pair<int,int> > >edges;

void findNeighbor(int pp,int qq){

    for(int i = 0,nni,nnj,ni,nj,dis ; i < 4;i++){
        nni = pp + mi[i];
        nnj = qq + mj[i];

        for(int j = -1;j<2;j++){
            dis=0;
            ni = nni;
            nj = nnj;
            if(i<2)nni+=j;
            else nnj+=j;
            while(valid(ni,nj,n,m) && color[ni][nj]==0)ni+=mi[i],nj+=mj[i],dis++;
            if(valid(ni,nj,n,m)){
                if(color[pp][qq]!=color[ni][nj] && color[ni][nj]){
                    edges.push_back({dis, {color[pp][qq],color[ni][nj]} });
                }
            }
        }

    }
}

int par[mxn2];

int findParent(int p){
    if(p==par[p])return p;
    return par[p]=findParent(par[p]);
}

int disconnected[mxn];

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int ca=0;
    memset(disconnected,0,sizeof(disconnected));

    while(scanf("%d %d ",&n,&m)){
        if(n==0 && m==0)break;

        col=1;

        for(int i =0  ; i < n ;i++)scanf("%s",&maze[i]);
        memset(color,0,sizeof(color));
        for(int i =0 ; i < n;i++){
            for(int j = 0 ; j < m;j++){
                if(color[i][j]==0 && maze[i][j]=='#'){
                    bfs(i,j);
                    col++;
                }
            }
        }

        ca++;
        if(ca!=1)printf("\n");
        printf("City %d\n",ca);

        edges.clear();

        for(int i = 0 ; i < n;i++){
            for(int j = 0 ; j < m ; j++){
                if(color[i][j]){
                    findNeighbor(i,j);
                }
            }
        }
        sort(edges.begin(),edges.end());

        for(int i = 0 ; i < col;i++)par[i]=i;

        if(col<=2){
            printf("No bridges are needed.\n");
            continue;
        }

        int edgesused = 0,curdis = 0;

        for( auto e:edges){
            int u = e.second.first;
            int v = e.second.second;
            int d = e.first;

            int pu = findParent(u);
            int pv = findParent(v);

            if(pu!=pv){
                edgesused++;
                curdis+=d;
                par[pu]=pv;
            }
        }

        if(edgesused == 0){
            printf("No bridges are possible.\n");
        }
        else if(edgesused==1){
            printf("1 bridge of total length %d\n",curdis);
        }
        else{
            printf("%d bridges of total length %d\n",edgesused,curdis);
        }

        if((edgesused+1)!=(col-1)){
            printf("%d disconnected groups\n",col-1-edgesused);
        }
    }
    return 0;
}
