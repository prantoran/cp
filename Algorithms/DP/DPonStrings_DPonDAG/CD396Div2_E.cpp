#include<bits/stdc++.h>
#define MAXN 111111
#define LL long long
#define PB push_back 
using namespace std;

int bits[MAXN][25];
int n;
vector<int> G[MAXN];

LL ans[MAXN];

LL dp[MAXN][25][2]; // dp[u][i][j] stores the number of paths
//that starts from u and the xor value of the paths for the 
// ith bit is j

void dfs(int u,int p){
	LL paths[25][2];
	//paths[i][j] for node u stores the number of paths for its children v
	//that excludes u but starts from node v and whose xor bit value at
	//ith position is j
	memset(paths,0,sizeof(paths));

	for(int i = 0 ;i < 25;i++)
		dp[u][i][bits[u][i]]=1; //path with u only, having xor value 
		// bits[u][i] for the jth position

	for(auto v:G[u]){
		if(v == p)continue;
		dfs(v,u);
		for(int i = 0 ; i < 25;i++){
			for(int j = 0 ; j < 2;j ++ ) {
				dp[u][i][j] += dp[ v ][ i ][ j^bits[u][i] ];
				//for the ith bit
				//adding the paths that start with v and has xor pathvalue 
				//j^bits[v][i] to u having xor pathvalue j, extending with u
				paths[i][j] += dp[v][i][j];
				//self-explanatory
			}
		}
	}
	//paths that start from u have been processed
	//now paths where u lies in the middle will be calculated
	for(int i = 0 ; i < 25; i ++ ) {
		LL x0 = 0 , x1 = 0;
		for(auto v:G[u]){
			if(v==p)continue;
			x0 += (paths[i][1]-dp[v][i][1])*dp[v][i][1];
			x0 += (paths[i][0]-dp[v][i][0])*dp[v][i][0];
			//x0 contains the paths whose xor path values for the ith position
			//is 0 and will contain v in the among the paths
			x1 += (paths[i][0]-dp[v][i][0])*dp[v][i][1];
			x1 += (paths[i][1]-dp[v][i][1])*dp[v][i][0];
			//x1 contains the paths whose xor path values for the ith position
			//is 1 and will contain v in the among the paths
		}
		//paths that contain child v and goes to a branch
		//that contains another child w of u must contain u in between v and w
		if(bits[u][i]){
			ans[i] += x0/2;	
		} else {
			ans[i] += x1/2;
		}
		//bits[u][i] is 1 then the xor of pathvalues of two branches containing  
		//u's children v and w must be 0 for the path to add positive ans for bit i
		//bits[u][i] is 0 then the xor of pathvalues of two branches containing  
		//u's children v and w must be 1 for the path to add positive ans for bit i
		 
	}
	for(int i = 0;i<25;i++){
		ans[i] += dp[u][i][1];
		//adding the paths which start at u and whose xor path value is 1
	}
}


int main(){
	freopen("in.txt","r",stdin);
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i = 1,x;i<=n;i++){
		cin>>x;
		for(int j = 0;j<25;j++){
			bits[i][j] = (bool) (x &(1<<j));
		}
	}
	for(int i = 1,u,v;i<n;i++){
		cin>>u>>v;
		G[u].PB(v);
		G[v].PB(u);
	}
	dfs(1,0);
	LL res = 0 ; 
	for(int i = 0 ; i < 25; i ++ ) {
		res += (ans[i]* (1LL<<i));
		//adding the ans[i](number of paths whose xor is 1)for bit i
		//multiplied by the power of the position of the bit i
	}
	cout<<res<<"\n";
	return 0;
}
