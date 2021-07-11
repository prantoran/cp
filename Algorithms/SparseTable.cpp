template <typename T>
struct SparseTable{
    vector <T> dp[32];
    T combine(const T& x, const T& y){
        return __gcd(x, y);
    }
 
    SparseTable(const vector<T> &ar){
        int i, j, l, h, n = (int)ar.size();
 
        dp[0] = ar;
        for (h = 1, l = 2; l <= n; h++, l <<= 1){
            dp[h].resize(n);
            for (i = 0, j = i + (l / 2); (i + l) <= n; i++, j++){
                dp[h][i] = combine(dp[h - 1][i], dp[h - 1][j]);
            }
        }
    }
 
    T query(int l, int r){
        // l, r inclusive, [l, r]
        int h = __lg(r - l); // returns largest bit position of the binary representation 
        return combine(dp[h][l], dp[h][r - (1 << h) + 1]);
    }
};
