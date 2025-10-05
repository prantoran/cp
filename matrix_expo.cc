// https://codeforces.com/blog/entry/80195
// https://leetcode.com/problems/number-of-zigzag-arrays-ii

const int MOD = 1e9 + 7;

class Matrix {
public:
    vector<vector<int>> m;
    int sz;
    Matrix(int n, bool ident=false): sz(n) {
        m.assign(n, vector<int>(n, 0));
        if (ident) {
            for (int i = 0; i < n; i ++) m[i][i] = 1;
        }
    }
    Matrix operator*(const Matrix &o) const {
        Matrix res(sz);
        for (int i = 0;i < sz; i ++) {
            for (int k = 0;k < sz; k ++) {
                if (!m[i][k]) continue;
                long long val = m[i][k];
                for (int j = 0;j < sz; j ++) {
                    res.m[i][j] = (res.m[i][j] + val * o.m[k][j]) % MOD;
                }
            }
        }
        return res;
    }
};

Matrix mpow(Matrix base, long long exp) {
    Matrix res(base.sz, true);
    while (exp > 0) {
        if (exp&1) res = res*base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}
