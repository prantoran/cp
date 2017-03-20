//http://codeforces.com/contest/785/problem/D
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

#define MAXN 222222
const ll MODD = 1000000007;
string s;
ll fact[MAXN];
ll prefix[MAXN],suffix[MAXN];
//prefix[i]: the number of opening brackets before pos i
//suffix[i]: the number of closing brackets after  pos i


ll ncr(ll n,ll r){
    if(n == r)return 1;
    return modS( modS(fact[n] * mod_inverse(fact[r],MODD),MODD)*mod_inverse(fact[n-r],MODD),MODD);
}

int main()
{
    #ifdef NSU_Prestige
        freopen ( "in.txt", "r", stdin );
    #endif
    fast_cin;
    cin>>s;
    int n = s.length();
    prefix[0] = suffix[n+1]=0;
    fact[0]=1;
    for(int i = 0 ;i<n;i++){
        int j = i+1;
        prefix[j] = prefix[j-1];
        fact[j] = (fact[j-1]*j)%MODD;
        if(s[i]=='(') prefix[j] ++;
    }
    for(int i = n-1;i>=0;i--){
        int j = i+1;
        suffix[j] = suffix[j+1];
        if(s[i]==')') suffix[j] ++;
    }
    ll ans = 0;
    for(int i = 0 ; i < n;i++){
        int j = i+1;
        if(s[i]==')' || suffix[j]==0)continue;
        ans = (ans + ncr(prefix[j]+suffix[j]-1,prefix[j]))%MODD; 
    }
    cout<<ans<<"\n";
    return 0;
}