//##################################PRANTORAN##############################################//

#include<bits/stdc++.h>

#define fr(a,b,c,d)     for(int a=b;a<c;a+=d)
#define inf             (1<<30)
#define sz              128

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

int tt , t , m , w , ac[ sz ][ sz ] , u , v , c , x , y , s , ans, lim, parents[ sz ] , flow ;

inline bool edmond_carp() {
    queue<int> q;
    fr(i,1,lim,1)parents[ i ] = 0;

    q.push( s );
    parents[ s ] = 2;
    while( !q.empty() ) {
        u = q.front();
        q.pop();
        fr(p,1,lim,1){
            if( !parents[ p ] && ac[ u ][ p ] > 0 ) {

                parents[ p ] = u;
                if( p == t ) return true;
                q.push( p );
            }
        }
    }

    return false;

}

inline void calc_flow() {
    u = parents[ t ], v = t, flow = inf;

    while( v != s ) {
        flow = min( flow , ac[ u ][ v ] );
        v = u;
        u = parents[ v ];
    }

    u = parents[ t ], v = t;

    while( v != s ) {
        ac[ u ][ v ] -= flow;
        ac[ v ][ u ] += flow;
        v = u;
        u = parents[ v ];
    }

    ans += flow;
}


int main(){

    tt = fi<int>();

    fr(ca,1,tt+1,1){

        m = fi<int>(); w = fi<int>();

        lim = (m<<1) + 2;
        s = 2;
        t = ( m<<1 ) + 1;

        fr(i,2,lim,1){
            fr(j,2,lim,1){
                ac[ i ][ j ] = 0;
            }
        }

        ac[ 2 ][ 3 ]   = inf;
        ac[ 3 ][ 2 ]   = inf;
        ac[ t-1 ][ t ] = inf;
        ac[ t ][ t-1 ] = inf;
        fr(i,2,m,1){
            u = i<<1;
            v = u + 1;

            ac[ u ][ v ] = fi<int>();
            ac[ v ][ u ] = ac[ u ][ v ];
        }

        while( w-- ) {

            u = fi<int>();
            v = fi<int>();
            c = fi<int>();

            u = u<<1;
            v = v<<1;

            ac[ u + 1 ][ v ] = c;
            ac[ v + 1 ][ u ] = c;

        }

        ans = 0;

        while( edmond_carp() ) {
            calc_flow();
        }
        printf("Case %d: %d\n",ca,ans);
    }
    return 0;
}
