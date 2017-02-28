//problem link: http://codeforces.com/contest/342/problem/E
/*
In this problem centroid decomposition was used
dis info for each node to its (max logn) centroids
ar calculated and updated
description: in this problem, a tree is given where
at the start, all nodes are blue but node 1 is red
In Update(u), node u is turned red, and (dis)ans for all of 
its centroids are updated
in Query(u), all the centroids of node u are visited
and best ans is picked
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 110000
#define INF 1111111111
int ans[MAXN];

#define CDSize 100005

//For Finding Distance of each node to its parent Centroids
#define FINDDIS
#define LOGX 18


int sz[CDSize], n, uu, vv;
int blocked[CDSize];
vector<int> G[CDSize];


//For Finding Distance of each node to its parent Centroids
int centroidLvl[CDSize];
int par[CDSize];
int dis[LOGX][CDSize];
//END

struct CentroidDecomposition{

    CentroidDecomposition(){}
     
    void getSize(int pos, int par) {
        sz[pos] = 1;
        for (int i=0; i<G[pos].size(); i++) {
            int j = G[pos][i];
            if (j == par) continue;
            if (blocked[j]) continue;
            getSize(j,pos);
            sz[pos] += sz[j];
        } return;
    }
     
    int getCenter(int pos, int par, int szz) {
        for (int i=0; i<G[pos].size(); i++) {
            int j = G[pos][i];
            if (j == par) continue;
            if (blocked[j]) continue;
            if (sz[j]+sz[j] > szz) return getCenter(j,pos,szz);
        } return pos;
    }
     
    int center(int pos) {
        getSize(pos,0);
        return getCenter(pos,0, sz[pos]);
    }
     

    //For Finding Distance of each node to its parent Centroids
    void SetDis(int u,int parent,int curLvl,int cenLvl){
        dis[cenLvl][u] = curLvl;
        for(int i = 0;i<G[u].size();i++){
            int j = G[u][i];
            if(blocked[j])continue;
            if(j==parent)continue;
            SetDis(j,u,curLvl+1,cenLvl);
        }
    }
    //END


    void decompose(int pos,int parent,int lvl) {
        int newCenter = center(pos);
        // Do your work here. Tree getting decomposed at newCenter


        //For Finding Distance of each node to its parent Centroids
        SetDis(newCenter,-1,0,lvl);
        par[newCenter] = parent;
        centroidLvl[newCenter]=lvl;
        ans[newCenter]=INF;
        //END


        blocked[newCenter] = 1;


        for (int i=0; i<G[newCenter].size(); i++) {
            int j = G[newCenter][i];
            if (blocked[j]) continue;
            decompose(j,newCenter,lvl+1);
        }
        return;
    }
 };

void Update(int u){
    int v    = u;
    int lvl  = centroidLvl[u];
    while(u != -1){
        int dist = dis[lvl][v]; lvl -- ;
        ans[u]   = min(ans[u],dist);
        u        = par[u]; //points to parent centroid
    }
}

int Query(int u){
    int ret = INF;
    int v   = u;
    int lvl = centroidLvl[u];
    while(u!=-1){ //par[u]==-1 means u is the first centroid
        int dist = dis[lvl][v]; lvl -- ;
        ret     = min(ret,ans[u]+dist);
        u       = par[u];
    } 
    return ret;
}


int main () {
    freopen("in.txt","r",stdin);

    CentroidDecomposition a;
    int q;
    scanf("%d %d", &n,&q);
    for (int i=1,uu,vv; i<n; i++) {
        scanf("%d %d", &uu, &vv);
        G[uu].push_back(vv);
        G[vv].push_back(uu);
    }
    
    a.decompose(1,-1,0);
    Update(1);
    for(int i = 0 ,tp,u;i<q;i++){
        scanf("%d %d",&tp,&u);
        if(tp==1)   Update(u);
        else        printf("%d\n",Query(u));
    }


    return 0;
}