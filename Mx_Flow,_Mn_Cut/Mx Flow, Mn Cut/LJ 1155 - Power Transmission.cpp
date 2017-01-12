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

#define fr(a,b,c,d)     for(int a=b;a<c;a+=d)
#define sz              203
#define inf             (1<<30)

typedef unsigned long long llu;

using namespace std;

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

int tt, n , s , t , m , rc[ sz ][ sz ] , ac[ sz ][ sz ] , u , v , w , flow, parents[ sz ] , ans, b, d, limit, nodes;

/*rc = residual capacity
ac = actial capacity
2*node = receiving node
2*node+1 = sending node
0 = global source
2*n + 2 = global sink
*/

inline bool edmond_carp() {
    fr(i,1,limit,1)parents[i] = 0;
    queue<int> q;
    q.push(s);
    parents[ s ] = 1;
    while( !q.empty() ) {
        u = q.front();
        q.pop();
        for( v = 1 ; v <limit ; v++ ) {
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
    //std::ios_base::sync_with_stdio(false);
    //cin.tie(false);

    #ifndef ONLINE_JUDGE
        freopen ( "input.txt", "r", stdin );
        //freopen ( "out.txt", "w", stdout );
    #endif

    tt = fi<int>();

    fr(ca,1,tt+1,1){

        n = fi<int>();

        limit = (n<<1) + 3;


        fr(i,1,limit,1){
            parents[ i ] = 0;
            fr(j,1,limit,1)
                rc[ i ][ j ] = 0,ac[ i ][ j ] = 0;
        }

        fr(i,1,n+1,1){
            w = fi<int>();

            u = i<<1;
            v = u|1;

            ac[ u ][ v ] = w;
            ac[ v ][ u ] = w;
        }

        m = fi<int>();

       while  ( m-- ) {
            u = fi<int>(); v = fi<int>(); w = fi<int>();
            u = (u<<1) | 1;
            v = (v<<1);
           ac[ u ][ v ] += w;
        }

       s = 1 , t = (n<<1) + 2;

        b = fi<int>(); d = fi<int>();

        while(b--){
            v = fi<int>();
            v = (v<<1);
            ac[ 1 ][ v ] = inf;
        }

        while( d-- ){
            u = fi<int>();
            u = (u<<1) | 1;
            ac[ u ][ t ] = inf;
        }

        ans = 0;

        while( edmond_carp() ) {
            calc_flow();
        }

        printf("Case %d: %d\n",ca,ans);
    }

    return 0;
}
