//ACM-ICPC Live Archive 3472 - Optical Fiber

#include<bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define ll long long
#define fr(a,b,c) for(int a=b;a<c;a++)
#define sqr(x) ( (x)*(x))

using namespace std;

typedef pair<int,int> pii;
typedef vector<int> vi;

const double pi = 2 * acos ( 0.0 );
const double eps = 1e-9;
const double inf = 123456789012;

//----------------------------------------------------

#define sz 1111

int n,ctcnt,ca;
vi edges[sz];
vector<pii> sites[sz];
map<string,int>nid;

double dp[sz][55];
int done[sz][55]={0};

double dis(pii xx,pii yy){
      return sqrt( (double)sqr(xx.ff-yy.ff) + (double)sqr(xx.ss-yy.ss) );
}

double f(int p,int id,int par){
      
      if(done[p][id]==ca)return dp[p][id];
      
      done[p][id]=ca;
      double sum = 0;
      
      fr(i,0,edges[p].size()){
            int v=edges[p][i];
            if(v==par)continue;
            
            double cur = inf;
            
            fr(j,0,sites[v].size()){
                  cur = min(cur,dis(sites[p][id],sites[v][j])+f(v,j,p));
            }
            
            sum +=cur;
      }
      return dp[p][id]=sum;
}

int main(){

      ca=1;
      freopen("input.txt","r",stdin);
      while(cin>>n,n){
            fr(i,0,n+1){
                  edges[i].clear();
                  sites[i].clear();
            }
            string ct,ct2;
            ctcnt=0;
            int sc,xx,yy;
            fr(i,0,n){
                  cin>>ct;
                  cin>>sc;
                  
                  nid[ct]=ctcnt++;
                  fr(j,0,sc){
                  
                        cin>>xx>>yy;
                        sites[i].pb(mp(xx,yy));
                  }
            }
            fr(i,1,n){
                  cin>>ct>>ct2;
                  edges[nid[ct]].pb(nid[ct2]);
                  edges[nid[ct2]].pb(nid[ct]);
            }
            
            double ans = inf;
            
           
            fr(i,0,sites[0].size()){
                  ans=min(ans,f(0,i,-1));
                  ca++;
            }
            printf("%.1lf\n",ans);
            
      }
      return 0;
}
