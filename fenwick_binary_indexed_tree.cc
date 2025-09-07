// https://leetcode.com/problems/sum-of-beautiful-subsequences

class Solution {
public:
    int totalBeauty(vector<int>& nums) {
        int n = (int)nums.size();
        int max_val = *max_element(nums.begin(), nums.end());
        const int MOD = 1'000'000'007;

        vector<vector<int>> divisors(max_val + 1);
        for (int d = 1; d <= max_val; d++) {
            for (int m = d; m <= max_val; m += d) {
                divisors[m].push_back(d);
            }
        }
        
        // A[d] = ordered list of [x, ...], where d is divisor of x and x is in nums vector,
        // and order of x's in nums vector is maintained in A[d].
        vector<vector<int>> A(max_val+1);
        A.shrink_to_fit(); // not all A[d]s are needed, releasing capacity of all at the start
        for (int x: nums) {
            for (int d: divisors[x]) {
                A[d].push_back(x);
            }
        }

        auto count_increasing = [&](const vector<int> & seq) -> int {
            if (seq.empty()) {
                return 0;
            }
            vector<int> vals = seq;
            sort(vals.begin(), vals.end());
            vals.erase(unique(vals.begin(), vals.end()), vals.end());
            int m = (int)vals.size();
            vector<int> bit(m + 1, 0);

            auto add = [&](int i, int v) {
                for (; i <= m; i += i&-i) {
                    int x = bit[i] + v;
                    if (x >= MOD) {
                        x -= MOD;
                    }
                    bit[i] = x;
                }
            };

            auto sum = [&](int i) {
                long long s = 0;
                for (;i > 0; i -= i&-i) {
                    s += bit[i];
                    if (s >= MOD) {
                        s -= MOD;
                    }
                }
                return (int)s;
            };

            long long total = 0;
            for (int v: seq) {
                // coordinate compression
                // fenwick/binary indexed tree is 1-indexed
                int r = int(lower_bound(vals.begin(), vals.end(), v) - vals.begin()) + 1; 
                int less = sum(r-1); // less than v
                int add_here = less + 1; // +1 for a single item subsequence containing v
                // in addition to all the previous sequences with endpoint less than v that 
                // gets suffixed with v.
                if (add_here >= MOD) {
                    add_here -= MOD;
                }
                add(r, add_here); // add_here = all subsequences with endpoint == v, added at compressed coordinated r.
                total += add_here;
                if (total >= MOD) {
                    total -= MOD;
                }
            }

            return (int)(total % MOD);
        };

        vector<int> num_inc(max_val + 1, 0); // num_inc[d] counts the number of increasing subsequences
        // in A that is divisible by d, wher d is not necessarily the gcd of the subsequence
        for (int x = 1; x <= max_val; ++x) {
            if (!A[x].empty()) {
                num_inc[x] = count_increasing(A[x]);
            }
        }

        vector<int> dp(max_val + 1, 0);
        for (int x = max_val; x >= 1; --x) {
            long long v = num_inc[x];
            for (int y = x+x; y <= max_val; y += x) {
                v -= dp[y];
                if (v < 0) v += MOD;
            }
            dp[x] = (int)v;
        }

        long long ans = 0;
        for (int x = 1; x <= max_val; x++) {
            if (dp[x]) {
                ans = (ans + 1LL * x * dp[x]) % MOD;
            }
        }

        return (int)ans;
    }
};
