//LightOJ 1405

#include<bits/stdc++.h>
#define mxe 20000*2*4+100
#define mxn 20000+100
#define inf 1<<30
using namespace std;



int t,n,m,ca,ec; 
//ec=edge count, head[i]=states the ec of the first edge info for node i
char s[111][111];
int cnt,source,sink;
int u[mxe],v[mxe],cap[mxe],flow[mxe],next[mxe],head[mxn];
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
int work[mxn];

inline void init(){
      memset(head,-1,sizeof(head));
      ec=0;
}

inline void addEdge(int uu,int vv,int val){
      u[ec]=uu,v[ec]=vv,cap[ec]=val,flow[ec]=0;
      next[ec]=head[u[ec]],head[u[ec]]=ec++;
      u[ec]=vv,v[ec]=uu,cap[ec]=0,flow[ec]=0;
      next[ec]=head[u[ec]],head[u[ec]]=ec++;
}

int dist[mxn],q[mxn];

inline bool bfs(){
      memset(dist,-1,sizeof(dist));
      dist[source]=0;
      int l=0,r=0;
      q[r++]=source;
      while(l<r){

            int x = q[l++];
            for(int i =head[x];i+1;i=next[i]){
                  if(flow[i]<cap[i] && dist[v[i]]==-1){
                        dist[v[i]]=dist[x]+1;
                        q[r++]=v[i];
                  }
            }
      }

      return dist[sink]!=-1;
}

int dfs(int x,int val){

      if(x==sink)return val;
      for(int &i=work[x];i+1;i=next[i]){
            int y=v[i],tmp;
            if(flow[i]<cap[i] && dist[y]==dist[x]+1 && (tmp=dfs(y,min(val,cap[i]-flow[i])))>0){
                  flow[i]+=tmp;
                  flow[i^1]-=tmp;
                  return tmp;
            }
            
      }
      return 0;
}

int dinic(int des){
      int ans = 0;
      while(bfs()){
            for(int i = 0 ; i <=des;i++)work[i]=head[i];
            while(1){
                  int tmp=dfs(source,inf);
                  if(!tmp)break;
                  ans+=tmp;
            }
      }
      return ans;
}

int main() {
      freopen("input.txt","r",stdin);
	
	scanf("%d",&t);
	for(ca=1;ca<=t;ca++){
            scanf("%d %d ",&n,&m);
            init();
            for(int i = 0 ; i < n;i++){
                  scanf("%s",s[i]);
            }
            cnt=0;
            source=2*n*m+1,sink=source+1;
            for(int i = 0 ; i  < n ; i ++){
                  for(int j = 0 ; j < m;j++){
                        int x = i*m+j; //receiver end of a pair representing a node with capacity 1
                        addEdge(x,x+n*m,1);
                        //all receiver ends are represented within n*m
                        //offset n*m is added to represent the sender end of the node
                        if(!i || !j || i==n-1 || j==m-1){
                              addEdge(x+n*m,sink,1);
                        }
                        else{
                              for(int k = 0;k<4;k++){
                                    int xx=i+dx[k],yy=j+dy[k];
                                    if(s[xx][yy]=='*')continue;
                                    addEdge(x+m*n,xx*m+yy,1);
                              }
                        }
                        if(s[i][j]=='*'){
                              addEdge(source,x,1);
                              cnt++;
                        }
                  }
            }
            printf("Case %d: ",ca);
            
            if(dinic(sink)==cnt)printf("yes\n");
            else printf("no\n");
	}
	return 0;
}
