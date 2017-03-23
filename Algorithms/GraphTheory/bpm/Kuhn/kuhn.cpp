
#include<bits/stdc++.h>
using namespace std;

/********** Solution ***************/
/*
1. kuhn.clear(n) ;
2. kuhn.adj[i].PB(j)  //edges must be directed from left to right
3. ans = kuhn.match(n) //n is number of left side node
4. if n is greater than 1000 then do Hopcroft Karp
5. kuhn.vertex_cover_print() //Print the selected vertex
*/

#define NODE 1003

struct KUHN{
	int left[NODE], right[NODE], vis[NODE], cc, LeftNode;
	vector<int> adj[NODE];

	KUHN() : cc(1) {}

	void clear( int n ) {
    	for(int i=0; i<=n; i++) adj[i].clear();
      LeftNode = n;
	}

	bool tryK ( int v ) {
    	if ( vis[v] == cc ) return false;
    	vis[v] = cc;
    	for ( int i = 0; i < adj[v].size(); i++ ) {
        	int t = adj[v][i];
        	if ( right[t] == -1 ) {
            	right[t] = v; left[v] = t;
            	return true;
        	}
    	}
    	for ( int i = 0; i < adj[v].size(); i++ ) {
        	int t = adj[v][i];
        	if ( tryK ( right[t] ) ) {
            	right[t] = v; left[v] = t;
            	return true;
        	}
    	}
    	return false;
	}

	int match(int n) {
    	int res = 0;
    	bool done;
    	memset(left,-1,sizeof(left));
    	memset(right,-1,sizeof(right));
    	do {
        	done = true; cc++;
        	for(int i=0; i<=n; i++) {
            	if(left[i]==-1 && tryK(i)) {
                	done = false;
            	}
        	}
    	} while(!done);
    	for(int i=0; i<=n; i++) res += (left[i]!=-1);
    	return res;
	}
}kuhn;

int main(){
    int n,k,m;
    scanf("%d",&n);
    kuhn.clear(n);
    for(int i =0 ; i < n;i++){
        scanf("%d",&m);
        for(int j = 0 ; j < m;j++){
            scanf("%d",&k);
            kuhn.adj[i].push_back(k);
        }

    }
    int bpm = kuhn.match(n);
    int ans = n-bpm;
    cout<<ans<<endl;
    return 0;

}
