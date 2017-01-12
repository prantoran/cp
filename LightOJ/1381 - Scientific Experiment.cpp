#include<bits/stdc++.h>
//#define LL long long
#define MAXN 1024
using namespace std;

#define gc getchar_unlocked

void readInt(int &x){
    register char c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}

int done[2][MAXN],dp[2][MAXN];
int t,x,y,z,n,ca;

int f(int notbroken,int p){
  //cout<<"notbroken:"<<notbroken<<"\tp:"<<p<<endl;
  if(p==0){
    if(notbroken)return x;
    return 0;
  }
  if(done[notbroken][p]==ca)return dp[notbroken][p];
  done[notbroken][p]=ca;
  int ret = INT_MAX;
  for(int i = 1;i<=p;i++){
    ret = min(ret,max(f(0,i-1),f(1,p-i)));
  }
  if(notbroken)ret+=z;
  else ret +=y;
  //cout<<"\tfin notbroken:"<<notbroken<<"\tp:"<<p<<endl;
  return dp[notbroken][p]=ret;

}

int main(){
  freopen("in.txt","r",stdin);
  //memset(done,0,sizeof(done));
  //scanf("%d",&t);
  readInt(t);
  for(ca=1;ca<=t;ca++){
    //scanf("%d %d %d %d",&n,&x,&y,&z);
    readInt(n);readInt(x);readInt(y);readInt(z);
    y+=x;
    x=-(x>>1);  //<<---------------------------divided by 2 and made negative
    //cout<<"x:"<<x<<"\ty:"<<y<<"\tz:"<<z<<"\tn:"<<n<<endl;
    printf("Case %d: %d\n",ca,f(0,n-1));
  }
  return 0;
} 