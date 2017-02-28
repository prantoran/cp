//http://codeforces.com/contest/321/problem/C

#include<bits/stdc++.h>
using namespace std;
#define MAXN 110000
char color[MAXN];

struct CentroidDecomposition{
    #define CDSize 100005
    int sz[CDSize], n, uu, vv;
    int blocked[CDSize];
    vector<int> v[CDSize];
    CentroidDecomposition(){}
     
    void getSize(int pos, int par) {
        sz[pos] = 1;
        for (int i=0; i<v[pos].size(); i++) {
            int j = v[pos][i];
            if (j == par) continue;
            if (blocked[j]) continue;
            getSize(j,pos);
            sz[pos] += sz[j];
        } return;
    }
     
    int getCenter(int pos, int par, int szz) {
        for (int i=0; i<v[pos].size(); i++) {
            int j = v[pos][i];
            if (j == par) continue;
            if (blocked[j]) continue;
            if (sz[j]+sz[j] > szz) return getCenter(j,pos,szz);
        } return pos;
    }
     
    int center(int pos) {
        getSize(pos,0);
        return getCenter(pos,0, sz[pos]);
    }
     
    void decompose(int pos,char ch) {
        int newCenter = center(pos);
        // Do your work here. Tree getting decomposed at newCenter
        color[newCenter] = ch;
        blocked[newCenter] = 1;
        for (int i=0; i<v[newCenter].size(); i++) {
            int j = v[newCenter][i];
            if (blocked[j]) continue;
            decompose(j,ch+1);
        }
        return;
    }
 };

int main () {
    freopen("in.txt","r",stdin);

    CentroidDecomposition a;
    scanf("%d", &a.n);
    for (int i=0,uu,vv; i<a.n-1; i++) {
        scanf("%d %d", &uu, &vv);
        a.v[uu].push_back(vv);
        a.v[vv].push_back(uu);
    }
    
    a.decompose(1,'A');   
    for(int i = 1;i<=a.n;i++){
        if(i>1)cout<<" ";
        cout<<color[i];
    } 
    return 0;
}