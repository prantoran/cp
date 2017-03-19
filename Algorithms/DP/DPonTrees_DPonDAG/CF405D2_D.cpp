//http://codeforces.com/contest/791/problem/D

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





//**********Stanford MathStuff END************/


/******* ! Code start from here ! *******/

#define MAXN 222222


int n,k;
vector<int> G[MAXN];
ll answer;

int totalSubTree[MAXN],countSubTree[MAXN][7];

int subtract(int i,int j){
    return ((i-j)%k + k)%k;
}

void dfs(int u,int par,int depth){
    totalSubTree[u] = countSubTree[u][depth%k] = 1;
    for(auto v:G[u]){
        if(v == par) continue;
        dfs(v,u,depth+1);
        for(int i = 0;i<k;i++)
            for(int j = 0 ; j < k;j++){
                int remainder = subtract(i+j,2*depth);
                int needs = subtract(k,remainder);
                answer += (ll)needs *countSubTree[u][i]*countSubTree[v][j];
            }
        for(int i = 0 ; i < k;i++)
            countSubTree[u][i] += countSubTree[v][i];
        totalSubTree[u]+=totalSubTree[v];
    } 
    answer += (ll)totalSubTree[u]*(n-totalSubTree[u]);
}

int main()
{
//     std::ios_base::sync_with_stdio(false);

        freopen ( "in.txt", "r", stdin );
//        freopen ( "out.txt", "w", stdout );

    /*
        Check overflows
        Dont assign sth that can be ll, or casted to ll, to an int variable
        Check extreme values [0,1,n]
        Limit to 3 nested if statements
        Prune obvious conditions earlier, making the problem smaller
        Take a cold shower, nap and wake up atleast an hour before contest

    */
    
    sf("%d %d",&n,&k);
    for(int i =1,u,v ; i< n;i++){
        sf("%d %d",&u,&v);
        G[u].pb(v);
        G[v].pb(u);
    }

    answer = 0;
    dfs(1,0,0);
    pf("%lld\n",answer /k);



    return 0;
}

/*
set<T>m;
m.insert(x); //insert x into set m
m.check(x); //returns iterator position to item x, returns m.end() if not found
*/