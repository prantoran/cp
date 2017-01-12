//##################################PRANTORAN##############################################//
/*
 Problem name :
 Algorithm : Not Sure Yet
 Contest/Practice :
 Source :
 Comment : I am hungry
 Date : --
 Last Update : 27-Jan-2015
*/

#include<bits/stdc++.h>

#define pause           system("pause");
#define ll              int
#define fr(a,b,c,d)     for(ll a=b;a<c;a+=d)
#define frr(a,b,c)      for(ll a=b;a>c;a--)
#define mod             1000000007
#define inf             1<<30
#define eps             1e-9
#define lcm(x,y)        (abs(x) /gcd(x,y))* abs(y)
#define pi              acos(-1.0)
#define what_is(x)      cerr<<#x<<" is "<<x<<"\n";
#define SQ(X)           X*X
#define sz              101

typedef unsigned long long llu;

using namespace std;

template<class T>
inline T mod_v(T num){
    if(num>=0)
        return num%mod;
    else
        return (num%mod+mod)%mod;
}

template<class T>
inline T gcd(T a,T b){
    a=abs(a);b=abs(b);
    while(b){a=a%b;swap(a,b); } return a;
}

template<class T>
T fast_pow(T n , T p){
    if(p==0) return 1;
    if(p%2){
        T g=mod_v ( mod_v(n) * mod_v(fast_pow(n,p-1)) );
        return g;
    }
    else{
        T g=fast_pow(n,p/2);
        g=mod_v( mod_v(g) * mod_v(g) ) ;
        return g;
    }
}

template<class T>
inline T modInverse(T n){
    return fast_pow(n,mod-2);
}

template<class T>
inline T fi(){
    register char c=0;
    register T a=0;
    bool neg=false;
    while(c<33)c=getchar();
    while(c>33){
        if(c=='-')neg=true;
        else a=a*10+c-'0';
        c=getchar();
    }
    return neg?-a:a;
}

double cosineRule3Side ( double a, double b, double c ) {
    double res = (SQ(a)+SQ(b)-SQ(c)) / (2*a*b);
    if ( res < -1 ) res = -1; if ( res > 1 ) res = 1;
    return acos ( res );
}

/******* ! Code start from here ! *******/

int tt, n , s , t , c , rc[ sz ][ sz ] , ac[ sz ][ sz ] , u , v , w , flow, parents[ sz ] , ans;
//rc = residual capacity
//ac = actial capacity

inline bool edmond_carp() {
    fr(i,1,n+1,1)parents[i] = 0;
    queue<int> q;
    q.push(s);
    parents[ s ] = 1;
    while( !q.empty() ) {
        u = q.front();
        q.pop();
        for( v = 1 ; v <= n ; v++ ) {
            if( !parents[ v ] && ac[ u ][ v ] > rc[ u ][ v ] ) {
                parents[ v ] = u;
                if ( v == t ) return true;
                q.push( v );
            }
        }

    }
    return false;
}

inline void calc_flow() {
    u = parents[ t ], v = t, flow = inf ;
    while( v != s ) {
        flow = min( flow , ac[ u ][ v ] - rc[ u ][ v ] );
        v = u;
        u = parents[ v ];
    }

    u = parents[ t ] , v = t;
    while( v != s ) {
        rc[ u ][ v ] += flow;
        rc[ v ][ u ] -= flow;
        v = u;
        u = parents[ v ];
    }
    ans += flow;

}
int main(){
    std::ios_base::sync_with_stdio(false);
    //cin.tie(false);

    #ifndef ONLINE_JUDGE
        freopen ( "input.txt", "r", stdin );
        //freopen ( "out.txt", "w", stdout );
    #endif

    tt = fi<int>();

    fr(ca,1,tt+1,1){

        n = fi<int>();

        fr(i,1,n+1,1){
            parents[ i ] = 0;
            fr(j,1,n+1,1)
                rc[ i ][ j ] = 0,ac[ i ][ j ] = 0;
        }

        s = fi<int>();t = fi<int>();c = fi<int>();

        while  ( c-- ) {
            u = fi<int>(); v = fi<int>(); w = fi<int>();
            ac[ u ][ v ] += w;
            ac[ v ][ u ] += w;
        }

        ans = 0;

        while( edmond_carp() ) {
            calc_flow();
        }

        printf("Case %d: %d\n",ca,ans);
    }

    return 0;
}
