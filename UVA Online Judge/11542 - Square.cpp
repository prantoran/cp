//UVA 11542 Square

// https://web.stanford.edu/~liszt90/acm/notebook

// Reduced row echelon form via Gauss-Jordan elimination
// with partial pivoting.  This can be used for computing
// the rank of a matrix.
//
// Running time: O(n^3)
//
// INPUT:    a[][] = an nxm matrix
//
// OUTPUT:   rref[][] = an nxm matrix (stored in a[][])
//           returns rank of a[][]

#include<bits/stdc++.h>

#define ll long long

using namespace std;

//const double EPSILON = 1e-10;

typedef int T; //double changed to int
typedef vector<T> VT;
typedef vector<VT> VVT;

int rref(VVT &a) {
  int n = a.size();
  int m = a[0].size();
  int r = 0;
  for (int c = 0; c < m && r < n; c++) {
    int j = r;
    for (int i = r; i < n; i++) //r+1 changed to r
      if (a[i][c]) j = i;
    if (a[j][c]==0) continue;
    swap(a[j], a[r]);
    //T s = 1.0 / a[r][c];
    //for (int j = 0; j < m; j++) a[r][j] *= s;
    for (int i = r+1; i < n; i++) {
        if(a[i][c]){

            for (int j = c; j < m; j++)a[i][j] ^= a[r][j];
        }
    }
    r++;
  }
  return r;
}

int pdx;
bool sieve[1111111];
ll primes[5555];

void findPrimes(){
    pdx=0;
    memset(sieve,0,sizeof(sieve));
    for(int i = 2;i<=500;i++){
        if(!sieve[i]){
            for(int j = i*i;j<=500;j+=2*i){
                sieve[j]=1;
            }
        }
    }
    for(int i = 2;i<=500;i++){
        if(!sieve[i]){
            primes[pdx++]=i;
        }
    }
}

int t , n ;
ll numbers[696];

VVT a,b;

int main(){
    //freopen("in.txt","r",stdin);
    findPrimes();

    cin>>t;
    while(t--){
        cin>>n;
        for(int i = 0; i < n ;i++){
            cin>>numbers[i];
        }

        a = VVT(n,VT(pdx+1));

        for(int i = 0 ; i < n;i++){
            for(int j = 0 ; j < pdx;j++){
                while(!(numbers[i]%primes[j])){
                    a[i][j]^=1;
                    numbers[i]/=primes[j];
                }
            }
        }
        int rnk = rref(a);
        cout<<((ll)1<<(n-rnk))-1<<"\n";
    }
    return 0;
}
