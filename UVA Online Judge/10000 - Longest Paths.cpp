#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mxn = 555;
int t,n,src,ca,done[mxn],u,v;
pair<int,int>dp[mxn];
vector<int>edges[mxn];

pair<int,int> f(int p){
    if(done[p]==ca)return dp[p];
    done[p]=ca;

    int ret= 0;
    int rpos = p;

    for(int v,i = 0, len = edges[p].size();i<len;i++){
        v=edges[p][i];

        pair<int,int> tmp = f(v);

        if(ret<tmp.first+1){
            ret = tmp.first+1;
            rpos = tmp.second;
        }
        else if(ret == (tmp.first+1) && rpos>tmp.second){
            ret = tmp.first+1;
            rpos = tmp.second;
        }
    }

    if(ret ==0){
        rpos = p;
    }
    return dp[p]= make_pair(ret,rpos);
}

int main(){
   // freopen("in.txt","r",stdin);
    memset(done,0,sizeof(done));

    for(ca=1;;ca++){
        scanf("%d",&n);
        if(n==0)break;

        scanf("%d",&src);
        for(int i = 0 ; i < mxn;i++)edges[i].clear();

        scanf("%d %d",&u,&v);

        while(u && v){
            edges[u].push_back(v);


            scanf("%d %d",&u,&v);
        }

        pair<int,int> ans = f(src);
        //cout<<"ans len:"<<ans.first<<"\tans pos:"<<ans.second<<endl;


        printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n",ca,src,ans.first,ans.second);

    }


    return 0;

}
