#include <iostream>
#include <cstdio>
#include <vector>

#define MX 200005
#define LL long long

using namespace std;

vector<int> c, d;

int inv2[MX];
int rmq[20][MX];

void setInv2() {
    int base = 1;
    int exponent = 0;
    for (int i = 1; i < MX; i ++) {
        if ((base<<1) == i) base <<= 1, exponent ++;
        inv2[i] =exponent;
    }
}

void setRMQ(int n, const vector<int>& arr) {
    memset(rmq, 0, sizeof rmq);

    for (int j = 0; j < n; j ++) {
        rmq[0][j] = arr[j];
    }

    int ln = inv2[n] + 1;

    int base = 1;
    for (int i = 1; i < ln; i ++) {
        for (int j = 0; j + 2*base -1 < n; j ++) {
            rmq[i][j] = max(rmq[i-1][j], rmq[i-1][j+base]);
        }

        base <<= 1;
    }

    base = 0;
    for (int i = 0; i < ln; i ++) {
        for (int j = 0; j + 2*base -1 < n; j ++) {
            cout << rmq[i][j] << " ";
        } cout << endl;

        if (!base) base = 1;
        else base <<= 1;
    }
}

int query(int l, int r) {
    int range = r-l+1;
    int ln = inv2[range];
    int base = 1 << ln;
    return max(rmq[ln][l], rmq[ln][r-base+1]);
}

bool p1(int l, int r, int v) {
   if (query(l, r) <= v) return true;
   return false; 
}

bool p2(int l, int r, int v, int k) {
    if (query(l, r) <= v + k) return true;
    return false;
}

bool p3(int l, int r, int v, int k) {
    if (query(l, r) < v - k) return true;
    return false;
}



LL binarySearchIntervals(int i, int mxlen, int v, int k, bool (*px)(int l, int r, int v, int k) ) {
    LL ret = 0;

    int lft = i;

    int lo = 0, hi = i;

    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        if (p1(mid, i, v) && (*px)(mid, i , v, k)) {
            hi = mid - 1;
            lft = mid;
        } else {
            lo = mid + 1;
        }
    }

    int rgt = i;

    lo = i, hi = mxlen-1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (p1(i, mid, v) && (*px)(i, mid, v, k)) {
            lo = mid + 1;
            rgt = mid;
        } else {
            hi = mid - 1;
        }
    }

    ret = (LL)(i - lft + 1) * (rgt - i + 1);

    return ret;
}

LL intervalsCWillWin(int i, int mxlen, int v, int k) {
    return binarySearchIntervals(i, mxlen, v, k, p2);
}

LL intervalsDWillLoose(int i, int mxlen, int v, int k) {
    return binarySearchIntervals(i, mxlen, v, k, p3);
}

int main() {
    freopen("data.in", "r", stdin);
    
    setInv2();

    int t;
    scanf("%d", &t);

    for (int ca = 1; ca <= t; ca ++) {
        int n, k;
        scanf("%d %d", &n, &k);

        c = vector<int> (n);
        d = vector<int> (n);

        for (int i = 0; i < n; i ++) {
            scanf("%d", &c[i]);
        }

        for (int i = 0; i < n; i ++) {
            scanf("%d", &d[i]);
        }

        setRMQ(n, d);

        cout << query(1, max(1, n-3) ) << endl;

        LL ans = 0;
        for (int i = 0 ; i < n; i ++) {
            LL cur = intervalsCWillWin(i, n-1, c[i], k) - intervalsDWillLoose(i, n-1, c[i], k);
            ans += cur;
        }

        printf("Case #%d: %lld\n", ca, ans);

    }


    return 0;
}