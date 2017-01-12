//SPOJ LIM
//GE code from https://web.stanford.edu/~liszt90/acm/notebook.html


// Gauss-Jordan elimination with full pivoting.
//
// Uses:
//   (1) solving systems of linear equations (AX=B)
//   (2) inverting matrices (AX=I)
//   (3) computing determinants of square matrices
//
// Running time: O(n^3)
//
// INPUT:    a[][] = an nxn matrix
//           b[][] = an nxm matrix
//
// OUTPUT:   X      = an nxm matrix (stored in b[][])
//           A^{-1} = an nxn matrix (stored in a[][])
//           returns determinant of a[][]

#include <iostream>
#include <vector>
#include <cmath>
#include<bits/stdc++.h>

using namespace std;

const double EPS = 1e-10;

typedef vector<int> VI;
typedef double T;
typedef vector<T> VT;
typedef vector<VT> VVT;

T GaussJordan(VVT &a, VVT &b) {
  const int n = a.size();
  const int m = b[0].size();
  VI irow(n), icol(n), ipiv(n);
  T det = 1;

  for (int i = 0; i < n; i++) {
    int pj = -1, pk = -1;
    for (int j = 0; j < n; j++) if (!ipiv[j])
      for (int k = 0; k < n; k++) if (!ipiv[k])
	if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) { pj = j; pk = k; }

    if (fabs(a[pj][pk]) < EPS) { cerr << "Matrix is singular." << endl; exit(0); }
    ipiv[pk]++;
    swap(a[pj], a[pk]);
    swap(b[pj], b[pk]);
    if (pj != pk) det *= -1;
    irow[i] = pj;
    icol[i] = pk;
    T c = 1.0 / a[pk][pk];
    det *= a[pk][pk];
    a[pk][pk] = 1.0;
    for (int p = 0; p < n; p++) a[pk][p] *= c;
    for (int p = 0; p < m; p++) b[pk][p] *= c;
    for (int p = 0; p < n; p++) if (p != pk) {
      c = a[p][pk];
      a[p][pk] = 0;
      for (int q = 0; q < n; q++) a[p][q] -= a[pk][q] * c;
      for (int q = 0; q < m; q++) b[p][q] -= b[pk][q] * c;
    }
  }

  for (int p = n-1; p >= 0; p--) if (irow[p] != icol[p]) {
    for (int k = 0; k < n; k++) swap(a[k][irow[p]], a[k][icol[p]]);
  }

  return det;
}

const int mxn = 666;

int m;
vector<int> edges[mxn];
VVT a,b;

double A[mxn][mxn],B[mxn][mxn];
int id[mxn],nid[mxn],pp;

int main() {
    //freopen("in.txt","r",stdin);
    while(scanf("%d",&m)){

        if(m==0)break;

        for(int i = 0 ; i < 500;i++)edges[i].clear();
        memset(id,-1,sizeof(id));
        memset(nid,-1,sizeof(nid));
        pp=0;

        for(int i = 0 , u , v ; i < m;i++){
            scanf("%d %d",&u,&v);
            if(id[u]==-1){
                id[u]=pp;
                nid[pp++]=u;
            }
            if(id[v]==-1){
                id[v]=pp;
                nid[pp++]=v;
            }

            edges[id[u]].push_back(id[v]);
            edges[id[v]].push_back(id[u]);
        }

        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));

        for(int len,i = 0 ; i <pp;i++){
            len =edges[i].size();
            A[i][i]=1;

            if(nid[i]<291){
                for(int j = 0,v ; j < len;j++){
                    v=edges[i][j];
                    A[i][v]=(double)(-1)/len;
                }
                B[i][0]=0;
            }
            else if(nid[i]<300){
                B[i][0]=0;
            }
            else{
                B[i][0]=1;
            }
        }

        a=VVT(pp);
        b=VVT(pp);

        for(int i = 0 ; i < pp;i++){
            a[i]=VT(A[i],A[i]+pp);
            b[i]=VT(B[i],B[i]+1);
        }

        double det = GaussJordan(a,b);

        printf("%.3f\n",b[id[0]][0]+EPS);
    }
    return 0;
}
