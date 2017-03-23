//http://codeforces.com/gym/100753/attachments
//2015 German Collegiate Programming Contest (GCPC 15) + POI 10-T3
//problem B

#include<bits/stdc++.h>
#define pause           system("pause");
#define mod             1000000007
#define inf             1<<30
#define pb              push_back
#define ppb             pop_back
#define mp              make_pair
#define F               first
#define S               second
#define sz(x)           ((int)x.size())
#define sqr(x)          ( (x)* (x) )
#define eps             1e-9
#define lcm(x,y)        (abs(x) /gcd(x,y))* abs(y)
#define all(x)          (x).begin(),(x).end()
#define pf              printf
#define sf              scanf
#define pi              acos(-1.0)
#define reset(x,v)      memset(x,v,sizeof(x));
#define what_is(x)      cerr<<#x<<" is "<<x<<"\n";
#define fast_cin        ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef unsigned long long llu;
using namespace std;
template<class T>
inline T mod_v(T num)
{
    if(num>=0)
        return num%mod;
    else
        return (num%mod+mod)%mod;
}
template<class T>
inline T gcd(T a,T b)
{
    a=abs(a);
    b=abs(b);
    while(b) b ^= a ^= b ^= a %= b;
    return a;
}
template<class T>
T fast_pow(T n , T p)
{
    if(p==0) return 1;
    if(p%2)
    {
        T g=mod_v ( mod_v(n) * mod_v(fast_pow(n,p-1)) );
        return g;
    }
    else
    {
        T g=fast_pow(n,p/2);
        g=mod_v( mod_v(g) * mod_v(g) ) ;
        return g;
    }
}
template<class T>
inline T modInverse(T n)
{
    return fast_pow(n,mod-2);
}
bool equalTo ( double a, double b ){ if ( fabs ( a - b ) <= eps ) return true; else return false; }
bool notEqual ( double a, double b ){if ( fabs ( a - b ) > eps ) return true; else return false; }
bool lessThan ( double a, double b ){ if ( a + eps < b ) return true; else return false; }
bool lessThanEqual ( double a, double b ){if ( a < b + eps ) return true;   else return false;}
bool greaterThan ( double a, double b ){if ( a > b + eps ) return true;else return false;}
bool greaterThanEqual ( double a, double b ){if ( a + eps > b ) return true;else return false;}
template<class T>
inline int in(register T& num)
{
    register char c=0;
    num=0;
    bool n=false;
    while(c<33)c=getchar();
    while(c>33){
        if(c=='-')
            n=true;
        else num=num*10+c-'0';
        c=getchar();
    }
    num=n?-num:num;
    return 1;
}
//**********Stanford MathStuff START************/
// return a % b (positive value)
template<class T>
T modS(T a, T b) {
    if(a>=0)return a%b;
    return ((a%b)+b)%b;
}
// returns d = gcd(a,b); finds x,y such that d = ax + by
template<class T>
T extended_euclid(T a, T b, T &x, T &y) {
    T xx = y = 0;
    T yy = x = 1;
    while (b) {
        T q = a/b;
        T t = b; b = a%b; a = t;
        t = xx; xx = x-q*xx; x = t;
        t = yy; yy = y-q*yy; y = t;
    }
    return a;
}
// computes b such that ab = 1 (mod n), returns -1 on failure
template<class T>
T mod_inverse(T a, T n) {
      T x, y;
      T d = extended_euclid(a, n, x, y);
      if (d > 1) return -1;
      return modS(x,n);
}

//**********Stanford MathStuff END************/
/******* ! Code start from here ! *******/


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




int main()
{
//     std::ios_base::sync_with_stdio(false);
    #ifdef prestige
        freopen ( "in.txt", "r", stdin );
//        freopen ( "out.txt", "w", stdout );
    #endif
    /*
        Check overflows
        Dont assign sth that can be ll, or casted to ll, to an int variable
        Check extreme values [0,1,n]
        Limit to 3 nested if statements
        Prune obvious conditions earlier, making the problem smaller
        Take a cold shower, nap and wake up atleast an hour before contest
    */
    int n,k,m;
    scanf("%d",&n);
    //cout<<"n:"<<n<<endl;
    kuhn.clear(n);
    for(int i =0 ; i < n;i++){
        scanf("%d",&m);
        for(int j = 0 ; j < m;j++){
            scanf("%d",&k);
            kuhn.adj[i].push_back(k);
        }

    }
   // cout<<"pass\n";
    int bpm = kuhn.match(n);
    int ans = n-bpm;
    printf("%d\n",ans);
    return 0;
}
/*
set<T>m;
m.insert(x); //insert x into set m
m.check(x); //returns iterator position to item x, returns m.end() if not found
*/
