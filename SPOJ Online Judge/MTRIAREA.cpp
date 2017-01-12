#include <bits/stdc++.h>
using namespace std;
 
#define MAX 100009
#define i64 long long
#define sq(x) ((x)*(x))
#define eps 1e-9
 
/*
ConvexHull : Graham's Scan O(n lg n), integer implementation
P[]: holds all the points, C[]: holds points on the hull
np: number of points in P[], nc: number of points in C[]
to handle duplicate, call makeUnique() before calling convexHull()
call convexHull() if you have np >= 3
to remove co-linear points on hull, call compress() after convexHull()
*/
 
struct point {
    i64 x, y;
} P[MAX], C[MAX], P0;
 
// P[] contains all points
// C[] contains convex hull ccw
 
 
inline i64 triArea2(const point &a, const point &b, const point &c) {
    return (a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y));
}
 
inline i64 sqDist(const point &a, const point &b) {
    return ((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
 
inline bool comp(const point &a, const point &b) {
    int d = triArea2(P0, a, b);
    if(d < 0) return false;
    if(!d && sqDist(P0, a) > sqDist(P0, b)) return false;
    return true;
}
 
inline bool normal(const point &a, const point &b) {
    return ((a.x==b.x) ? a.y < b.y : a.x < b.x);
}
 
inline bool issame(const point &a, const point &b) {
    return (a.x == b.x && a.y == b.y);
}
 
inline void makeUnique(int &np) {
    sort(&P[0], &P[np], normal);
    np = unique(&P[0], &P[np], issame) - P;
}
 
void convexHull(int &np, int &nc) {
    int i, j, pos = 0;
    for(i = 1; i < np; i++)
        if(P[i].y<P[pos].y || (P[i].y==P[pos].y && P[i].x<P[pos].x))
            pos = i;
    swap(P[0], P[pos]);
    P0 = P[0];
    sort(&P[1], &P[np], comp);
    
    for(i = 0; i < 3; i++) C[i] = P[i];
    for(i = j = 3; i < np; i++) {
        while(triArea2(C[j-2], C[j-1], P[i]) < 0) j--;
        C[j++] = P[i];
    }
    nc = j;
  
}
 
void compress(int &nc) {
    int i, j, d;
    C[nc] = C[0];
    for(i=j=1; i < nc; i++) {
        d = triArea2(C[j-1], C[i], C[i+1]);
        if(d || (!d && issame(C[j-1], C[i+1]))) C[j++] = C[i];
    }
    nc = j;
}
 
int n,nc;
 
int main(){
   // freopen("in.txt","r",stdin);
    while(scanf("%d",&n),n!=-1){
        for(int i = 0 ; i < n;i++){
            scanf("%lld %lld",&P[i].x,&P[i].y);
        }
       
       makeUnique(n);
        convexHull(n,nc);
        compress(nc);
      
 
        i64 ans = 0,tmp ;
 
        for(int i = 0 ;i < nc;i++){
           
            for(int j = i+1,k= i+2; j<k && j<nc && k<nc;j++){
                tmp = abs(triArea2(C[i],C[j],C[k]));
                
                while( k+1<nc && ( tmp<abs(triArea2(C[i],C[j],C[k+1]) )) ){
                    tmp = abs(triArea2(C[i],C[j],C[k+1]) );
                    k++;
                }

                ans = max(ans,tmp);
 
            }
        }
        //cout<<fixed<<setprecision(2)<<((double)ans)/2<<"\n";
        printf("%.2lf\n",(double)ans/2);
    }
    return 0;
}