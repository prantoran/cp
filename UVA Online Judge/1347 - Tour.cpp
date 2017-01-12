#include<bits/stdc++.h>
using namespace std;

int t,n;
double x[105],y[105];
double dp[105][105][105],dis[105][105];
int done[105][105][105],ca;

double f(int p,int l,int r){
//cout<<"p:"<<p<<"\tl:"<<l<<"\tr:"<<r<<endl;
  if(p==(n-1) ){
      return dis[l][p]+dis[r][p];
  }
  if(done[p][l][r]==ca)return dp[p][l][r];
  done[p][l][r]=ca;
  double ret = 1e10;
  ret = min(f(p+1,p,r)+dis[l][p],f(p+1,l,p)+dis[r][p]);
  return dp[p][l][r]=ret;
}

int main(){
  //freopen("in.txt","r",stdin);
  ios_base::sync_with_stdio(0);
  cin.tie(0);
    ca=1;
    while(cin>>n){
      for(int i = 0 ; i < n;i++){
          cin>>x[i]>>y[i];
      }
      for(int i = 0 ; i < n;i++){
        for(int j = 0 ; j < n;j++){
          dis[i][j]=hypot(x[i]-x[j],y[i]-y[j]);
        }
      }

      double ans = f(1,0,0);
      //printf("%.2lf\n",ans);
      cout<<fixed<<setprecision(2)<<ans<<"\n";
    ca++;
  }

  return 0;

}
