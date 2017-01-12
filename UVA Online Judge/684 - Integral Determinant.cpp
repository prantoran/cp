//UVA 684 - Integral Determinant
//tag:finding integral determinant
#include<bits/stdc++.h>
using namespace std;

const double EPS = 1E-9;

int determinant(vector<vector<int>> a,int n){
     int cnt = 0;
     int ans = 1;
     for(int i = 0; i < n; i++){
         for(int j = i+1; j < n; j++){
             int x, y;
             x = i, y = j;
             while(a[y][i]){
                 int t = a[x][i] / a[y][i];
                 for(int k = 0; k < n; k++){
                     a[x][k] = a[x][k] - a[y][k]*t;
                 }
                 swap(x, y);
             }
             if(x != i){
                for(int k = 0; k < n; k++){
                     swap(a[x][k], a[y][k]);
                 }
                 cnt ^= 1;
             }
        }
         if(a[i][i] == 0){
             ans = 0; break;
         }
         else ans *= a[i][i];
     }
     if(cnt) ans *= -1;
     return ans;
 }

int n;

vector<vector<int> > A;

int main(){
    //freopen("in.txt","r",stdin);
    while(scanf("%d",&n)!=EOF){
        if(n==0){
            printf("*\n");
            break;

        }
        A = vector<vector<int> > (n, vector<int> (n));
        for(int i = 0 ; i < n;i++){
            for(int j = 0 ; j < n;j++){
                scanf("%d",&A[i][j]);
            }
        }
        printf("%d\n",determinant(A,n));

    }
    return 0;
}
