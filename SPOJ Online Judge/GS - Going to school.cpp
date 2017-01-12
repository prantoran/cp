//copied from Stanford ACM notebook
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

//tag: Gaussian Elimination

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
  int n = a.size();
  int m = b[0].size();

  //cout<<"n:"<<n<<"\tm:"<<m<<endl;

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

int n ,t, m,src,snk;
int deg[111];

int main() {

    //freopen("in.txt","r",stdin);
      scanf("%d",&t);
      while(t--){
        memset(deg,0,sizeof(deg));
        scanf("%d %d %d",&n,&src,&snk);
        src--,snk--;
        VVT a(n,VT(n));

        for(int i = 1,u,v,cost;i<n;i++){
            scanf("%d %d %d",&u,&v,&cost);
            u--,v--;
            a[u][v]=a[v][u]=cost;
            deg[u]+=cost,deg[v]+=cost;
        }
        for(int i = 0;i<n;i++){
            for(int j = 0 ; j <  n;j++){
                if(i==j)a[i][i]=1;
                else a[i][j]=a[i][j]/-deg[i];
            }
        }
        for(int i = 0 ; i  <n;i++)a[i].erase(a[i].begin()+snk);
        a.erase(a.begin()+snk);

        VVT ones(n-1);
        for(int i = 0 ; i < n-1;i++){
            ones[i]=vector<double>();
            ones[i].push_back(1);
            ones[i].push_back(1);
        }

        double det = GaussJordan(a,ones);

        double ans;
        //cout<<"src:"<<src<<"\tsnk:"<<snk<<endl;
        if(src==snk)ans=0;
        else if(src<snk)ans=ones[src][0];
        else ans=ones[src-1][0];
        printf("%.5f\n",fabs(ans));
      }

      return 0;
}
