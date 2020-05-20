#include <iostream>
#define LL long long
#define MOD 1000000007
using namespace std;


class Matrix {
    
    public:
    LL a[3][3];  

    Matrix() {
        for(int i = 0; i < 3; i ++)
            for(int j = 0; j < 3; j ++)
                a[i][j] = 0;    
    }

    void setupTransformMat() {
        a[0][0] = 0;
        a[0][1] = 1;
        a[0][2] = 0;

        a[1][0] = 1;
        a[1][1] = 1;
        a[1][2] = 1;

        a[2][0] = 0;
        a[2][1] = 0;
        a[2][2] = 1;
    }

    Matrix exponentiate(int N) {
        Matrix result = Matrix();

        if (!N) return result;

        for(int i = 0; i < 3; i ++)
            result.a[i][i] = 1;
        
        Matrix tmp = Matrix();
        for(int i = 0; i < 3; i ++)
            for(int j = 0; j < 3; j ++) 
                tmp.a[i][j] = a[i][j];
        
        while (N) {
            if (N%2) {
            
                result.matmul(tmp.a);
            }

            tmp.matmul(tmp.a);
            N /= 2;
        }

        return result;
    }

    void matmul(LL b[][3]) {
        
        LL c[3][3];
        for(int i = 0; i < 3; i ++)
            for(int j = 0; j < 3; j ++)
                c[i][j] = 0;

        for (int i = 0; i < 3; i ++)
            for (int j = 0; j < 3; j ++) 
                for (int k = 0; k < 3; k ++) 
                    c[i][j] = (c[i][j] + ((a[i][k]*b[k][j])%MOD)) % MOD;
        

        for (int i = 0; i < 3; i ++) 
            for(int j = 0; j < 3; j ++)
                a[i][j] = c[i][j];
    }
};


LL solve(LL N, LL M) {
    
    Matrix A = Matrix();
    
    A.setupTransformMat();

    LL sum1 = 0;
    if (N > 0) {
        Matrix Nexp = A.exponentiate(N-1);
        sum1 = Nexp.a[1][2];
    }

    Matrix Mexp = A.exponentiate(M);
    LL sum2 = Mexp.a[1][2];

    return (sum2-sum1+MOD)%MOD;
}


int main() {

    int t;
    LL N, M;
   
    scanf ("%d", &t);
    for (int ca = 1; ca <= t; ca ++) {
        scanf("%lld %lld", &N, &M);
        
        printf("%lld\n", solve(N, M));

    }
    
    return 0;
}