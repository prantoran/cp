//POJ 1703
//Find Them, Catch Them
//http://poj.org/problem?id=1703
//Tag: MST

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int mxn = 111111;

int t,n,m,u,v,par[mxn],tag[mxn];
char tp;

int findPar(int p){
    if(p==par[p])return p;
    int pp = findPar(par[p]);
    tag[p]=(tag[p]^tag[par[p]]); //alternate tag of immediate neighbour
    return par[p]=pp;
}

int main(){
   // freopen("in.txt","r",stdin);

    scanf("%d",&t);

    while(t--){
        scanf("%d %d ",&n,&m);

        for(int i = 0 ; i <=n;i++ ){
            par[i]=i;
            tag[i]=0;
        }

        while(m--){
            scanf("%c %d %d ",&tp,&u,&v);
            int pu = findPar(u);
            int pv = findPar(v);
           // cout<<"tp:"<<tp<<"\tu:"<<u<<"\tv:"<<v<<"\tpu:"<<pu<<"\tpv:"<<pv<<endl;
            //tag of root of tree is always 0
            if(tp=='D'){
                if(pu!=pv){ //not yet part of same tree
                    par[pv]=pu;
                    if(tag[u]){
                        tag[pv]=tag[v];
                    }
                    else{
                        tag[pv]=1-tag[v];
                    }
                }
            }
            else{
                if(pu!=pv){
                    printf("Not sure yet.\n");
                }
                else{
                    if(tag[u]!=tag[v]){
                        printf("In different gangs.\n");
                    }
                    else{
                        printf("In the same gang.\n");
                    }
                }
            }

        }


    }

    return 0;
}
