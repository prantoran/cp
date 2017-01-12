#include<bits/stdc++.h>
using namespace std;

//Lemma:
const int mxn = 44444;
const int inf = 1<<30;
const int NIL = 0; //extra node, all unassigned nodes assigned
int Pair_U[mxn],Pair_V[mxn];
int Dist[mxn]; // always on U
int U,V; //starts from 1

queue<int>Q;
vector<int>Adj[mxn]; //directed, from u in U to v in V

bool BFS(){
    while(!Q.empty())Q.pop();
    for(int u = 1;u<=U;u++){
        if(Pair_U[u]==NIL){
            Dist[u]=0;
            Q.push(u);
        }
        else{
            Dist[u]=inf;
        }
    }
    Dist[NIL]=inf;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        if(Dist[u] < Dist[NIL]){
            for(int v,i = 0,len=Adj[u].size() ; i  <len;i++){
                v=Adj[u][i];
                if( Dist[Pair_V[v]] == inf ){
                    Dist[ Pair_V[v] ] = Dist[u] + 1;
                    Q.push(Pair_V[v]);
                }
            }
        }
    }
    return Dist[NIL] != inf; //Dist of NIL is not inf then an unmatched node in V is found

}

bool DFS(int u){
    if( u!= NIL ) {
        for(int v,i = 0,len=Adj[u].size() ; i  <len;i++){
            v = Adj[u][i];
            if(Dist[ Pair_V[v] ] == Dist[u] + 1){
                if ( DFS(Pair_V[v]) ){

                    Pair_V[v]=u;
                    Pair_U[u]=v;
                    return true;
                }
            }
        }
        Dist[u]=inf;
        return false;
    }
    //NIL node reached, hence free node in V found
    return true;
}

int Hopcroft_Karp(){
    for(int u = 1;u<=U;u++){
        Pair_U[u]=NIL;
    }
    for(int v = 1;v<=V;v++){
        Pair_V[v]=NIL;
    }
    int matching = 0;
    while( BFS() ) {
        for(int u = 1;u<=U;u++){
            if(Pair_U[u] == NIL ){
                if ( DFS(u) ){
                    matching=matching+1;
                }
            }
        }
    }
    return matching>>1;
}
//complexity of one while loop: O( (V+E)//bfs + (V+E)//dfs)
//,, ,, all while loop at worst case: O( V*(V+E) ) ~ O(VE)


/*** FAST I/O ***/

//#define gc getchar
#define gc getchar_unlocked
#define vlong long long 
void readInt(int &x){
    register char c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}

void readVlong (vlong &x){
    register char c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}

void readChar ( char &x ) {
    register char c = gc();
    while (c < 33) c = gc();
    x = c;
}

void readString(char *str){
    register char c = 0;
    register int i = 0;
    while (c < 33)
        c = gc();
    while (c != '\n') {
        str[i] = c;
        c = gc();
        i = i + 1;
    }
    str[i] = '\0';
}

/*** FAST I/O Ends ***/


const int MAX = 500001;
bool sieve[MAX];

int t,n,ca,a[MAX];
int primes[MAX],pdx;

int mark[MAX],lim;

int main(){
    freopen("in.txt","r",stdin);
    
    //memset(sieve,0,sizeof(sieve));
    for(int i = 4;i<MAX;i+=2)sieve[i]=1;
    for(int i = 3;i*i<=MAX;i+=2){
        if(sieve[i]==0){
            for(int j = i*i;j<MAX;j+=i<<1){
                sieve[j]=1;
            }
        }
    }

    primes[0]=2;
    pdx = 1;
    for(int i = 3;i<MAX;i+=2)if(sieve[i]==0)primes[pdx++]=i;
    
    //scanf("%d",&t);
    readInt(t);
    for(ca=1;ca<=t;ca++){
        //scanf("%d",&n);
        readInt(n);
        lim = -1;
        memset(mark,0,sizeof(mark));
        for(int i = 1;i<=n;i++){
            //scanf("%d",&a[i]);
            readInt(a[i]);
            lim = max(lim,a[i]);
            mark[a[i]]=i;
        }
        
        U = n, V = n;
        for(int i = 0;i<=U;i++)Adj[i].clear();
        for(int u,i = 1;i<=n;i++){
            u = a[i];
            for(int v,j = 0 , p ; j < pdx;j++){
                p = primes[j];
                v = p*u;
                if(v>lim)break;
                if(mark[v] && mark[v]!=i){
                        Adj[i].push_back(mark[v]);
                        Adj[mark[v]].push_back(i);
                }
            }
        }
        printf("Case %d: %d\n",ca,n-Hopcroft_Karp());
    }
    return 0;
}