#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


const int MX = 200000;

typedef long long ll;
typedef pair<ll, ll> pll;

ll primes[] = {999983, 999979};
ll MODS[] = {1000000009, 1000000007};
ll primesInv[2];

ll extendeEuclid (ll A, ll B, ll *X, ll *Y ){
    ll x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1; y2 = 0; x1 = 0; y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y ) {
        q = r2 / r1; r = r2 % r1;
        x = x2 - (q * x1); y = y2 - (q * y1);
    }
    *X = x2; *Y = y2;
    return r2;
}


ll modInv ( ll a, ll m ) {
    ll x, y;
    ll _ = extendeEuclid( a, m, &x, &y );
    x %= m;
    if ( x < 0 ) x += m;
    return x;
}

ll powers[2][MX], powersInv[2][MX];
char S[2][MX];
int N[2];

ll hashes[2][2][MX];

ll rangeHash(int hashID, int strID, int lft, int rgt) {

    ll ret = ((hashes[hashID][strID][rgt] - hashes[hashID][strID][lft-1])*powersInv[hashID][lft-1]) % MODS[hashID];

    if (ret < 0) ret += MODS[hashID];
    return ret;
}


vector<pll> possible;

bool check(int len) {
    if (!len) return true;

    possible.clear();

    for (int i = 1, j = len; j <= N[0]; i ++, j ++) {
        possible.push_back(pll(rangeHash(0, 0, i, j), rangeHash(1, 0, i, j)));
    }

    sort(possible.begin(), possible.end());

    for (int i = 1, j = len; j <= N[1]; i ++, j ++) {
        pll key = pll(rangeHash(0, 1, i, j), rangeHash(1, 1, i, j));
        if (binary_search(possible.begin(), possible.end(), key))
            return true;
    }

    return false;
}

int main() {
    //freopen("data.in", "r", stdin);

    for (int i = 0;i < 2; i ++)
        scanf("%s ", S[i]);

    N[0] = strlen(S[0]), N[1] = strlen(S[1]);


    for (int i = 0; i < 2; i ++)
        primesInv[i] = modInv(primes[i], MODS[i]);


    powers[0][0] = powers[1][0] = powersInv[0][0] = powersInv[1][0] = 1;

    for (int j = 1; j < max(N[0], N[1]); j ++) {
        for (int i = 0; i < 2; i ++) {

            powers[i][j] = (powers[i][j-1]*primes[i]) % MODS[i];

            powersInv[i][j] = (powersInv[i][j-1]*primesInv[i]) % MODS[i];
        }

    }


    for (int i = 0; i < 2; i ++) { // over string
        for (int j = 1; j <= N[i]; j ++) { // over length
            for (int k = 0; k < 2; k ++) { // over primes-hash
                hashes[k][i][j] = (hashes[k][i][j-1] + powers[k][j-1]*S[i][j-1]) % MODS[k];
            }
        }
    }

    int lo = 0, hi = min(N[0], N[1]), ans = -1, mid;

    while (lo <= hi) {
        mid = (lo+hi) / 2;
        if (check(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    printf("%d", ans);

    return 0;
}
