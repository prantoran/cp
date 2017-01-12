#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mxn = 1111;
const ll inf = (ll)1<<60;

int P,V;
ll E,a[mxn],c[mxn],d[mxn];
char name[200];
map<string,int >id;
char lst[100000];
vector<int>edges[mxn];

int done[mxn][mxn],ca;
ll dp[mxn][mxn];
ll f(int p,int q){ //p=villain, q=superpower
    if(p>V){
        return 0;
    }
    if(q>P){
        return inf;
    }
    if(done[p][q]==ca)return dp[p][q];
    done[p][q]=ca;
    ll ret =inf;
    
    for(auto v:edges[p]){

        if(v>=q && a[v]>=d[p]){
            ret = min(ret, c[v] + f(p+1,v+1));
        }
    }
    return dp[p][q]=ret;
}

int main(){

    //freopen("in.txt","r",stdin);
    memset(done,0,sizeof(done));
    ca=1;
    while(scanf("%d %d %lld ",&P,&V,&E),P||V||E){
        
        for(int i = 1;i<=P;i++){
            scanf("%s %lld %lld ",name,&a[i],&c[i]);
            id[name]=i;
        }
        for(int i = 1;i<=V;i++){
            edges[i].clear();
            scanf("%s %lld %s",name,&d[i],lst);
            char *p =strtok(lst,",");
            while(p!=NULL){
                sscanf(p,"%s",name);
                edges[i].push_back(id[name]);
                p = strtok(NULL,",");
            }
            sort(edges[i].begin(),edges[i].end());
        }

        
        ll ans =f(1,1);
        if(ans<=E){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
        ca++;
    }
    return 0;
}
