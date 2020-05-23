#include <cstdio>
#include <algorithm>
#define LL long long
#define MX 100005
using namespace std;

bool sieve[MX];

int  sid;
LL sq[MX];

int main() {
    for (int i = 4; i < MX; i += 2) sieve[i] = 1;
    for (int i = 3; i*i < MX; i += 2) {
        if (sieve[i]) continue;
        for (int j = i*i; j < MX; j += 2*i) sieve[j] = 1;
    }

    sq[0] = 4;
    sid = 1;
    for (LL i = 3; i < MX; i += 2) if (!sieve[i]) sq[sid++] = i*i;

    int t;
    LL n, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld %lld", &n, &k);

        int lo = 0, hi = sid-1, ans1 = 0;

        while (lo <= hi) {
            int mid = (lo+hi)/2;
            if (sq[mid] <= n) {
                ans1 = mid+1;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        int ans2 = 0;
        lo = 0, hi = sid-1;
        while (lo <= hi) {
            int mid = (lo+hi)/2;
            // printf("\sq[%d]:%lld\n", mid, sq[mid]);
            if (sq[mid] <= k) {
                ans2 = mid+1;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        if (k >= n) ans2 = ans1;

        printf("%d %d\n", ans1, ans1-ans2);

    }

    return 0;
}