// https://leetcode.com/problems/valid-k-unique-subarrays-i

class Solution {
    public boolean[] validSubarrays(int[] nums, int k, int[][] queries) {
        final int N = nums.length;
        final int M = queries.length;
        final int blockSZ = (int)Math.sqrt(N);
        int iqueries[][] = new int[M][3];
        for (int i = 0 ; i < M; i ++) {
            iqueries[i][0] = queries[i][0];
            iqueries[i][1] = queries[i][1];
            iqueries[i][2] = i;
        }
        Arrays.sort(iqueries, (a, b) -> {
            int blkA = a[0]/blockSZ;
            int blkB = b[0]/blockSZ;
            if (blkA != blkB) {
                return Integer.compare(blkA, blkB);
            } 
            return (blkA&1) == 1? Integer.compare(b[1], a[1]): Integer.compare(a[1], b[1]);
        });
        boolean ans[] = new boolean[M];
        int L = 0, R = -1;
        int distinct = 0;
        int odd = 0;
        
        Function<int[], Integer> findMax = arr -> {
            int mxm = 0;
            for (int i = 0; i < arr.length; i ++) {
                mxm = Math.max(mxm, arr[i]);
            }
            return mxm;
        };

        int maxVal = findMax.apply(nums);
        int freq[] = new int[maxVal + 1];
        for (int iQ[]: iqueries) {
            int l = iQ[0];
            int r = iQ[1];
            int idx = iQ[2];
            
            while (L > l) {
                L--;
                freq[nums[L]]++;
                if (freq[nums[L]] == 1) distinct++;
                if (freq[nums[L]]%2 == 1) odd++;
                else odd--;
            }

            while (R < r) {
                R++;
                freq[nums[R]]++;
                if (freq[nums[R]] == 1) distinct++;
                if (freq[nums[R]]%2 == 1) odd++;
                else odd--;
            }

            while (L < l) {
                freq[nums[L]]--;
                if (freq[nums[L]] == 0) distinct--;
                if (freq[nums[L]]%2 == 1) odd++;
                else odd--;
                L++;
            }

            while (R > r) {
                freq[nums[R]]--;
                if (freq[nums[R]] == 0) distinct--;
                if (freq[nums[R]]%2 == 1) odd++;
                else odd--;
                R--;
            }

            if (distinct==k && odd==0) {
                ans[idx] = true;
            }
        }

        return ans;
    }
}
