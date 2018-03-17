
class SegmentTree {
    private int n;
    private long[] min, add;

    SegmentTree(int sz) {
        n = 1;
        while (n < sz) {
            n *= 2;
        }
        min = new long[2 * n];
        add = new long[2 * n];
    }

    private void clear(int i, int tl, int tr) {
        min[i] = 0;
        add[i] = 0;
        if (tl == tr - 1) {
            return;
        }
        int tm = (tl + tr) / 2;
        clear(2 * i + 1, tl, tm);
        clear(2 * i + 2, tm, tr);
    }

    void clear(int n) {
        this.n = n;
        clear(0, 0, n);
    }

    private void push(int i, int tl, int tr) {
        min[i] += add[i];
        if (tl != tr - 1) {
            add[2 * i + 1] += add[i];
            add[2 * i + 2] += add[i];
        }
        add[i] = 0;
    }

    private void add(int i, int tl, int tr, int l, int r, long delta) {
        push(i, tl, tr);
        if (l >= tr || r <= tl) {
            return;
        }

        if (l <= tl && tr <= r) {
            add[i] += delta;
            push(i, tl, tr);
            return;
        }

        int tm = (tl + tr) / 2;
        add(2 * i + 1, tl, tm, l, r, delta);
        add(2 * i + 2, tm, tr, l, r, delta);
        min[i] = Math.min(min[2 * i + 1], min[2 * i + 2]);
    }

    private long get(int i, int tl, int tr, int l, int r) {
        push(i, tl, tr);
        if (l >= tr || r <= tl) {
            return Long.MAX_VALUE;
        }

        if (l <= tl && tr <= r) {
            return min[i];
        }

        int tm = (tl + tr) / 2;
        return Math.min(get(2 * i + 1, tl, tm, l, r), get(2 * i + 2, tm, tr, l, r));
    }

    void add(int l, int r, long delta) {
        add(0, 0, n, l, r + 1, delta);
    }

    long get(int l, int r) {
        return get(0, 0, n, l, r + 1);
    }
}