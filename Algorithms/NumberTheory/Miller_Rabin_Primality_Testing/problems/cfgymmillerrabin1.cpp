
//http://codeforces.com/gym/100753

#include<bits/stdc++.h>
using namespace std;

/* this function calculates (a*b)%c taking into account that a*b might overflow */
typedef unsigned long long ULL;
//% operation is expensive. Find ways to avoid it

//Cakculate a * b % c without overflow. Taken from Top Coder
template<class T>
T mulmod(T a,T b,T c){
    if(a<b)swap(a,b);
    T x = 0,y=a%c;
    while(b > 0){
        if(b&1){
            x = x+y;
            if(x>=c)x-=c;
            //x = (x+y)%c;
        }
        y = (y*2);
        if(y>=c)y-=c;
        b>>=1;
    }
    return x%c;
}

/* This function calculates (ab)%c */
template<class T>
T modulo(T a,T b,T c){
    T x=1,y=a; // long long is taken to avoid overflow of intermediate results
    while(b > 0){
        if(b&1){
            x=mulmod(x,y,c);
        }
        y = mulmod(y,y,c); // squaring the base
        b >>=1;
    }
    return x%c;
}

/* Smallest odd number for which Miller-Rabin primality test on bases <= n-th prime does not reveal compositeness.
2047, 1373653, 25326001, 3215031751, 2152302898747, 3474749660383, 341550071728321, 341550071728321, 3825123056546413051, 3825123056546413051, 3825123056546413051 */



//#######################################################################

#define ll long long
/*
template<class T>
T mulmod ( T a, T b, T c ) {
    if ( a < b ) swap ( a, b );
    T res = 0, x = a;
    while ( b > 0 ) {
        if ( b & 1 ) {
            res = res + x;
            if ( res >= c ) res -= c;
        }
        x = x * 2;
        if ( x >= c ) x -= c;
        b >>= 1;
     }
     return res % c;
}
*/
/** Smallest odd number for which Miller-Rabin primality test on bases <= n-th prime does not reveal compositeness.
2047, 1373653, 25326001, 3215031751, 2152302898747, 3474749660383, 341550071728321, 341550071728321,
3825123056546413051, 3825123056546413051, 3825123056546413051 **/

ll prime[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };
int psize = 13;

template<class T>
T bigmod ( T a, T p, T mod ) {
    T x = a, res = 1;
    while ( p ) {
        if ( p & 1 ) res = mulmod( res, x, mod );
        x = mulmod( x, x, mod );
        p >>= 1;
    }
    return res;
}

///Witness to compositeness of n
///n - 1 = 2^s * d, where d is odd

template<class T>
bool witness ( T a, T d, T s, T n ) {
    T r = bigmod( a, d, n );
    if ( r == 1 || r == n - 1 ) return false;
    int i;
    for ( i = 0; i < s - 1; i++ ) {
        r = mulmod( r, r, n );
        if ( r == 1 ) return true;
        if ( r == n - 1 ) return false;
    }
    return true;
}

template<class T>
bool Miller_Rabin ( T n ) {
    if ( n <= 1 ) return false;

    int i;
    T p = n - 1;
    T s = 0;
    while ( ! ( p & 1 ) ) {
        p /= 2;
        s++;
    }
    T d = p;
    p = n - 1;

    for ( i = 0; i < psize && prime[i] < n; i++ ) {
        if ( witness ( prime[i], d, s, n ) ) return false;
    }
    return true;
}

ll mp[20];
char buff[111];

int main(){
    freopen("in.txt","r",stdin);
    mp[0]=0; mp[1]=1; mp[2]=2; mp[3]=-1; mp[4]=-1; mp[5]=5;
    mp[6]=9; mp[7]=-1; mp[8]=8; mp[9]=6;

    long long n;

    scanf("%lld",&n);
    if(!Miller_Rabin(n)){
        printf("no\n");
    }else{
        sprintf(buff,"%lld",n);
        int len = strlen(buff);
        long long m = 0;
        for(int i = len -1;i>=0;i--){
            if(mp[buff[i]-'0']==-1){
                printf("no\n");
                return 0;
            }
            m = m*10LL + mp[buff[i]-'0'];
        }
        if(!Miller_Rabin(m)){
            printf("no\n");

        }else{
            printf("yes\n");
        }
    }

    return 0;

}
