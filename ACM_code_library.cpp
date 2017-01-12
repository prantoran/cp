/*
    Contents:
    1.kmp
    2.suffix array
    3.lcp using suffix array


*/


#include<bits/stdc++.h>
#define sz 100
using namespace std;

//1. kmp

int b[sz],m,n; //m=length,b[i]=border of prefixes of lengths 0 to m+1
char p[sz]; //pattern
char t[sz]; //search string

void preprocess(){
    int i = 0, j = -1;
    b[i]=j;
    while(i<m){
        while(j>=0 && p[i]!=p[j])j=b[j];
        i++;j++;
        b[i]=j;
    }
}
void kmpSearch(){
    int i=0, j=0;
    while (i<n){
        while (j>=0 && t[i]!=p[j]) j=b[j];
        i++; j++;
        if (j==m){
           // report(i-j);
            j=b[j];
        }
    }
}

//lcp=longest common prefix
//lca=least common ancestor

//2.suffix array complexity O(n lg^2(n))

#define MAXN 65536
#define MAXLG 17
char A[MAXN];

struct entry{
    int nr[2],p;
}L[MAXN];
int P[MAXLG][MAXN],N,i,stp,cnt;

int cmp(entry a, entry b){
    return a.nr[0] == b.nr[0] ? ( a.nr[1] < b.nr[1] ? 1 : 0 ) : ( a.nr[0] < b.nr[0] ? 1: 0);
}

void suffix_array_build(){
    //gets(A);
    for( N = strlen(A) , i = 0 ; i < N ; i++){
        P[0][i] = A[i] - 'a';
    }
    for( stp = 1 , cnt = 1 ; cnt>>1 < N ; stp++, cnt<<= 1 ){
        for( i = 0 ; i < N ; i++ ) {
            L[i].nr[0] = P[stp-1][i];
            L[i].nr[1] = i + cnt < N ? P[stp-1][i+cnt] : -1;
            L[i].p     = i;
        }
        sort(L, L + N, cmp);
        for( i = 0 ; i < N ; i++ ) {
            P[stp][ L[i].p ] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i -1].nr[1] ? P[stp][L[i - 1].p] : i ;
        }
    }
    return;
}

//3.lcp using suffix array

//lcp between two suffixes of a string ; complexity O ( lg(n) )
int lcp( int x, int y ) {
    int k , ret = 0;
    if ( x == y ) return N - x;
    for( k = stp - 1; k >= 0 && x < N && y < N; k-- ) {
        if(P[k][x] == P[k][y]){
            x += 1 << k, y += 1 << k, ret += 1 << k;
        }
    }
    return ret;
}



int main(){return 0;}
