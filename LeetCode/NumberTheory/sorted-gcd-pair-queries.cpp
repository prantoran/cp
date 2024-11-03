// https://leetcode.com/problems/sorted-gcd-pair-queries
class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        // find divisors count
        int mx = *max_element(nums.begin(), nums.end());
        vector<int> divCnt(mx+1, 0);
        for (int u: nums) {
            for (int d = 1; d <= floor(sqrt(u)); d++) {
                if (u%d) continue;
                divCnt[d] ++;
                if (u/d == d) continue;
                divCnt[u/d] ++;
            }
        }

        // find number of pairs with each gcd
        vector<long long> gcdCnt(mx+1, 0);
        for (int i = mx; i > 0; i --) {
            gcdCnt[i] = ((long long)divCnt[i] * (divCnt[i]-1)) / 2;
            for (int j = 2*i; j <= mx; j += i) {
                gcdCnt[i] -= gcdCnt[j];
            }
        }

        // prefix sum
        vector<long long> prefixSum (mx+1, 0);
        for (int i = 1; i <= mx; i ++) {
            prefixSum[i] = prefixSum[i-1] + gcdCnt[i];
        }

        // handle queries with binary search
        vector<int> ans;
        for (long long q: queries) {
            int lo = 1, hi = mx;
            int res = -1;
            while (lo <= hi) {
                int mid = (lo+hi)/2;
                if (prefixSum[mid] > q) {
                    res = mid;
                    hi = mid-1;
                } else {
                    lo = mid + 1;
                }
            }
            ans.push_back(res);
         }
        return ans;
    }
};
