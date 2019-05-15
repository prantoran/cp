// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051706/0000000000122838

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

#define MX 100005
#define LL long long

using namespace std;

int c[MX], d[MX], lastseen[MX];
int rmqC[20][MX], rmqD[20][MX];


int inv2[MX];

void setInv2() {
    int base = 1;
    int exponent = 0;
    for (int i = 1; i < MX; i ++) {
        if ((base<<1) == i) base <<= 1, exponent ++;
        inv2[i] =exponent;
    }
}

void setRMQ(int arr[], int n, int rmq[20][MX]) {
    int ln = inv2[n] + 1;

    for (int j = 0; j < n; j ++) {
        rmq[0][j] = arr[j];
    }

    int base = 1;
    for (int i = 1; i < ln; i ++) {
        for (int j = 0; j + 2*base -1 < n; j ++) {
            rmq[i][j] = max(rmq[i-1][j], rmq[i-1][j+base]);
        }

        base <<= 1;
    }
}

int query(int l, int r, const int rmq[20][MX]) {
    int range = r-l+1;
    int ln = inv2[range];
    int base = 1 << ln;
    return max(rmq[ln][l], rmq[ln][r-base+1]);
}

bool p1(int l, int r, int v) {
   if (query(l, r, rmqC) <= v) {
       return true;
   }

   return false; 
}

bool p2(int l, int r, int v, int k) {
    if (query(l, r, rmqD) <= v + k) {
        return true;
    }

    return false;
    
}

bool p3(int l, int r, int v, int k) {
    if (query(l, r, rmqD) < v - k) return true;
    return false;
}



LL binarySearchIntervals(int i,int firstpos, int lastpos, int v, int k, bool (*px)(int l, int r, int v, int k) ) {
    LL ret = 0;

    int lft = i+1;

    int lo = firstpos, hi = i;

    while(lo <= hi) {
        int mid = (lo + hi) / 2;

        if (p1(mid, i, v) && (*px)(mid, i , v, k)) {
            hi = mid - 1;
            lft = mid;
        } else {
            lo = mid + 1;
        }
    }

    int rgt = i-1;

    lo = i, hi = lastpos;

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

LL intervalsCCanWin(int i, int mxlen, int v, int k) {
    LL ret = binarySearchIntervals(i, lastseen[v]+1, mxlen, v, k, p2);
    return ret;
}

LL intervalsDWillLoose(int i, int mxlen, int v, int k) {
    LL ret = binarySearchIntervals(i, lastseen[v] + 1, mxlen, v, k, p3);
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

        for (int i = 0; i < n; i ++) {
            scanf("%d", &c[i]);
        }

        for (int i = 0; i < n; i ++) {
            scanf("%d", &d[i]);
        }
        
        memset(lastseen, -1, sizeof lastseen);

        setRMQ(d, n, rmqD);
        setRMQ(c, n, rmqC);

        LL ans = 0;
        for (int i = 0 ; i < n; i ++) {
            LL cur = intervalsCCanWin(i, n-1, c[i], k) - intervalsDWillLoose(i, n-1, c[i], k);
            ans += cur;
            lastseen[c[i]] = i;
        }

        printf("Case #%d: %lld\n", ca, ans);
    }

    return 0;
}