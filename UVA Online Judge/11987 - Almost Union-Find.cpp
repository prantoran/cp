#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mxn= 211111;
int n , m,par[mxn],cardinality[mxn],u,v ,root[mxn],tp,p,q;
ll sum[mxn];

int findPar(int pp){
    if(root[pp])return pp;

    return findPar(par[pp]);
}

int main(){
    //freopen("in.txt","r",stdin);
    while(scanf("%d %d",&n,&m)!=EOF){
        for(int i = 1;i<=n;i++){
            par[i]=n+i;
            sum[n+i]=i;
            cardinality[n+i]=1;
            root[n+i]=1;
        }

        while(m--){
            scanf("%d %d",&tp,&p);
            if(tp==3){
                p = findPar(par[p]);
                printf("%d %lld\n",cardinality[p],sum[p]);
            }
            else{
                scanf("%d",&q);
                if(tp==1){
                    u = findPar(par[p]);
                    v = findPar(par[q]);

                    if(u==v)continue;

                    par[u]=v;

                    sum[v]+=sum[u];
                    cardinality[v]+=cardinality[u];

                    root[u]=0;
                }
                else{
                    u = findPar(par[p]);
                    v = findPar(par[q]);

                    if(u==v)continue;

                    sum[u]-=p;
                    cardinality[u]--;
                    sum[v]+=p;
                    cardinality[v]++;

                    par[p]=v;
                }
            }

        }
    }
    return 0;
}
