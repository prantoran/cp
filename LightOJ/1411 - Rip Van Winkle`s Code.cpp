#include<bits/stdc++.h>
#define ll long long 
#define mxn 1060055
using namespace std;

const int MAXD = 262144;
int t,n,ca;
int xx,yy,zz;
char tp;
int qtype; //query type
ll ans;

struct data{
  ll sum,acnt,bcnt,delta,cval;
  bool cflag;
  void set(ll _sum,ll _a=0,ll _b=0,ll _d=0,ll _cv=0,ll _cf=0){
    sum  = _sum;
    acnt = _a;
    bcnt = _b;
    delta= _d;
    cval = _cv;
    cflag= _cf;
  }
  void setSum(ll _sum){sum=_sum;}
  void clearFlags(){acnt=0,bcnt=0,delta=0,cval=0,cflag=0;}
}tree[mxn];

inline void fixLaziness(int node,int start,int end){
  int lc = node<<1, rc = lc|1, mid = (start+end)>>1;
  if(tree[node].cflag){
    if(start<end){
      tree[lc].set(0,0,0,0,tree[node].cval,1);
      tree[rc].set(0,0,0,0,tree[node].cval,1);
    }
    tree[node].setSum(tree[node].cval * ( end - start + 1)); //just changing sum
    tree[node].cflag = 0; //turning of command C flag
  }
  
  //updating current node sum
  ll nsum = ((ll)(end-start+1)*(end-start+2))>>1;
  tree[node].sum +=              nsum*tree[node].acnt;
  tree[node].sum +=              nsum*tree[node].bcnt;
  tree[node].sum += (ll)(end-start+1)*tree[node].delta;
  
  if(start!=end){
    //propagating acnt,bcnt and delta to left child
    nsum            = (end-mid)*tree[node].bcnt;
    tree[lc].delta += (tree[node].delta+nsum);
    tree[lc].acnt  += tree[node].acnt;
    tree[lc].bcnt  += tree[node].bcnt;
      
    //propagating acnt,bcnt and delta to right child
    nsum            = (mid+1-start)*tree[node].acnt;
    tree[rc].delta += (tree[node].delta+nsum);
    tree[rc].acnt  += tree[node].acnt;
    tree[rc].bcnt  += tree[node].bcnt;
  }
  //clearing acnt,bcnt and delta of current node
  tree[node].clearFlags();
}

void propagate(int node,int start,int end){
  int lc = node<<1, rc = lc|1, mid = (start+end)>>1;
  if(qtype==3){
    tree[node].set((ll)(end-start+1)*zz,0,0,0,0,0);
    tree[lc].set(0,0,0,0,zz,1);
    tree[rc].set(0,0,0,0,zz,1);
    return;
  }
  if(qtype==1){
    tree[node].sum +=((ll)(start-xx)*(end-start+1) + (((ll)(end-start+1)*(end-start+2))>>1) ); 
    tree[lc].acnt  ++;
    tree[lc].delta +=(start-xx);
    tree[rc].acnt  ++;
    tree[rc].delta +=(mid-xx+1);
    return;    
  }
  if(qtype==2){ 
    tree[node].sum  +=((ll)(yy-end)*(end-start+1))  + (((ll)(end-start+1)*(end-start+2)>>1) );
    tree[lc].bcnt  ++;
    tree[lc].delta +=(yy-mid);
    tree[rc].bcnt  ++;
    tree[rc].delta +=(yy-end);
  }
}
/*strategy:
  when at a node, make change immediately, 
  push for laziness for children
*/
void update(int node,int start,int end){
  fixLaziness(node,start,end);
  if(start>yy || end<xx)return;
  if(xx<=start && end<=yy){
    propagate(node,start,end);
    return;
  }
  int mid = (start+end)>>1, lc  = node<<1, rc  = lc|1;
  update(lc,start,mid);
  update(rc,mid+1,end);
  tree[node].sum = tree[lc].sum+tree[rc].sum;
}

void query(int node,int start,int end){
  fixLaziness(node,start,end);
  if(start>yy || end<xx)return;
  if(xx<=start && end<=yy){
    ans += tree[node].sum;
    return;
  }
  int mid = (start+end)>>1, lc  = node<<1, rc  = lc|1;
  query(lc,start,mid);
  query(rc,mid+1,end);
  tree[node].sum = tree[lc].sum+tree[rc].sum;
}

int main(){
  freopen("in.txt","r",stdin);
  scanf("%d",&t);
  for(ca=1;ca<=t;ca++){
    scanf("%d ",&n);
    memset(tree,0,sizeof(tree));
    printf("Case %d:\n",ca);
    for(int i = 0 ; i < n;i++){
      scanf("%c %d %d ",&tp,&xx,&yy);
      if(tp == 'S'){
        ans = 0 ;
        query(1,1,MAXD);
        printf("%lld\n",ans);
        continue;
      }
      if(tp=='A'){ 
        qtype = 1;
      }
      else if(tp=='B'){
        qtype = 2;
      }
      else if(tp=='C'){
        scanf("%d ",&zz);
        qtype = 3;
      }
      update(1,1,MAXD);
    }
  }
  return 0;
}