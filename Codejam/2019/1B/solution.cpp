#include <iostream>
#include <cstdio>
#include <vector>

#define MX 200005
#define LL long long

using namespace std;

vector<int> c, d;
vector<vector<int> > rmqC, rmqD;

int inv2[MX];

void setInv2() {
    int base = 1;
    int exponent = 0;
    for (int i = 1; i < MX; i ++) {
        if ((base<<1) == i) base <<= 1, exponent ++;
        inv2[i] =exponent;
    }
}

void setRMQ(int n, const vector<int>& arr, vector<vector<int> >& rmq) {
    int ln = inv2[n] + 1;

    rmq = vector<vector<int> > (ln);

    rmq[0] = vector<int> (n);

    for (int j = 0; j < n; j ++) {
        rmq[0][j] = arr[j];
    }


    int base = 1;
    for (int i = 1; i < ln; i ++) {
        rmq[i] = vector<int> (n - 2*base + 1);
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

int query(int l, int r, const vector<vector<int> > rmq) {
    int range = r-l+1;
    int ln = inv2[range];
    int base = 1 << ln;

    cout << "query() range:" << range << " l:" << l << " r:" << r << " base:" << base << " ln:" << ln << " r-base+1:" << r-base+1 << " lft:" << rmq[ln][l] << " rgt:" << rmq[ln][r-base+1] << endl;
    return max(rmq[ln][l], rmq[ln][r-base+1]);
}

bool p1(int l, int r, int v) {
    cout << "p1() l:" << l << " r:" << r << " v:" << v << " query():" << query(l, r, rmqC) << endl;
   if (query(l, r, rmqC) <= v) {
       cout << "\ttrue\n";

       return true;
   }
   cout << "\tfalse\n";
   return false; 
}

bool p2(int l, int r, int v, int k) {
    cout << "p2() l:" << l << " r:" << r << " v:" << v << " k:" << k << endl;
    if (query(l, r, rmqD) <= v + k) {
        cout << "\ttrue\n";
        return true;
    }
    cout << "\tfalse\n";
    return false;
    
}

bool p3(int l, int r, int v, int k) {
    if (query(l, r, rmqD) < v - k) return true;
    return false;
}



LL binarySearchIntervals(int i, int lastpos, int v, int k, bool (*px)(int l, int r, int v, int k) ) {
    LL ret = 0;

    int lft = i+1;

    int lo = 0, hi = i;
    cout << "lft side\n";

    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        cout << "\tmid:" << mid << "\tlo:" << lo << "\thi:" << hi << endl;

        if (p1(mid, i, v) && (*px)(mid, i , v, k)) {
            hi = mid - 1;
            lft = mid;
        } else {
            lo = mid + 1;
        }
    }

    int rgt = i-1;

    lo = i, hi = lastpos;
    cout << "rgt side\n";

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        cout << "\tmid:" << mid << "\tlo:" << lo << "\thi:" << hi << endl;

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

LL intervalsCCanWin(int i, int mxlen, int v, int k) {
    LL ret = binarySearchIntervals(i, mxlen, v, k, p2);
    cout << "intervalsCCanWin() ret:" << ret << endl;
    return ret;
}

LL intervalsDWillLoose(int i, int mxlen, int v, int k) {
    LL ret = binarySearchIntervals(i, mxlen, v, k, p3);
    cout << "intervalsDWillLoose() ret:" << ret << endl;
    return ret;
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

        setRMQ(n, d, rmqD);
        setRMQ(n, c, rmqC);

        cout << query(1, max(1, n-3), rmqC) << endl;

        LL ans = 0;
        for (int i = 0 ; i < n; i ++) {
            LL cur = intervalsCCanWin(i, n-1, c[i], k) - intervalsDWillLoose(i, n-1, c[i], k);
            ans += cur;
        }

        printf("Case #%d: %lld\n", ca, ans);
    }

    return 0;
}