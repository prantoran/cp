//##################################PRANTORAN##############################################//

#include<bits/stdc++.h>

#define ll              int
#define fr(a,b,c,d)     for(ll a=b;a<c;a+=d)
#define inf             1<<30
#define sz              64

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


/******* ! Code start from here ! *******/

int tt, n , s , t , m , rc[ sz ][ sz ] , ac[ sz ][ sz ] , u , v , w , flow, parents[ sz ] , ans, limit;
//rc = residual capacity
//ac = actial capacity
string inp;
map<string,int>tsize;

inline bool edmond_carp() {
    fr(i,0,limit,1)parents[i] = -1;
    queue<int> q;
    q.push(s);
    parents[ s ] = 1;
    while( !q.empty() ) {
        u = q.front();
        q.pop();
        for( v = 0 ; v < limit ; v++ ) {
            if( parents[ v ]==-1 && ac[ u ][ v ] > rc[ u ][ v ] ) {
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
}
int main(){

    #ifndef ONLINE_JUDGE
        freopen ( "input.txt", "r", stdin );
        //freopen ( "out.txt", "w", stdout );
    #endif

    tsize["XXL"]=1;
    tsize["XL"]=2;
    tsize["L"]=3;
    tsize["M"]=4;
    tsize["S"]=5;
    tsize["XS"]=6;

    tt = fi<int>();

    fr(ca,1,tt+1,1){

        n = fi<int>(), m = fi<int>();

        s = 0, t = 7 + m;

        limit = t + 1;

        fr(i,0,limit,1){
            fr(j,0,limit,1)
                rc[ i ][ j ] = 0,ac[ i ][ j ] = 0;
        }

        fr(i,1,7,1){
            ac[ 0 ][ i ] = n;
        }

        fr(i,1,m+1,1){
            ;
            v = i + 6;

            ac[ v ][ t ] = 1;

            cin>>inp;
            u = tsize[inp];

            ac[ u ][ v ] += 1;

            cin>>inp;
            u = tsize[inp];
            ac[ u ][ v ] += 1;

        }
        ans = 0;

            while( edmond_carp() ) {
                calc_flow();
            }

            fr(i,1,m+1,1){
                u = i + 6;
                if( rc[ u ][ t ] > 0 ) ans++;
            }


        printf("Case %d: ",ca);

        if( ans == m ) {
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }

    return 0;
}
