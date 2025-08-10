class SegmentTree {
    int n;
    vector<vector<int>> tree;

    int getDepth(long long x) {
        int d = 0;
        while (x > 1) {
            x = __builtin_popcountll(x);
            d ++;
        }
        return d;
    }

    void build(int l, int r, int node, const vector<long long>& nums) {
        if (l == r) {
            int d = getDepth(nums[l]);
            tree[node][d] = 1;
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, node*2, nums);
        build(mid + 1, r, node*2 + 1, nums);
        for (int i = 0; i < 6; i ++)
            tree[node][i] = tree[node*2][i] + tree[node*2 + 1][i];
    }

    int query(int ql, int qr, int l, int r, int node, int k) {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return tree[node][k];
        int mid = (l+r)/2;
        return query(ql, qr, l, mid, node*2, k) + 
            query(ql, qr, mid+1, r, node*2 + 1, k);
    }

    void update(int idx, long long val, int l, int r, int node) {
        if (l == r) {
            tree[node] = vector<int>(6, 0);
            int d = getDepth(val);
            tree[node][d] = 1;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(idx, val, l, mid, node*2);
        else
            update(idx, val, mid+1, r, node*2 + 1);
        for (int i = 0; i < 6; i ++)
            tree[node][i] = tree[node*2][i] + tree[node*2 + 1][i];
    }

public:
    SegmentTree(const vector<long long>& nums) {
        n = nums.size();
        tree.assign(4*n, vector<int>(6, 0));
        build(0, n-1, 1, nums);
    }

    int getCount(int l, int r, int k) {
        return query(l, r, 0, n-1, 1, k);
    }

    void update(int idx, long long val) {
        update(idx, val, 0, n-1, 1);
    }
};
