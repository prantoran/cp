
#include <cstdio>
#include <iostream>
#define MX 10000006

using namespace std;

#if DEBUG == 2
    #include <iostream>
    #define LOG(x) cerr << #x <<":" << x << "\n"
#elif defined(DEBUG)
    #include <iostream>
    #define LOG(x) cerr << "concise:" << x << "\n";
#else
    #define LOG(x)
#endif

using u64 = long long;

int nextPrime[MX], phi[MX];

u64 ans[MX];

bool isAnagram[MX];

int digcnt[10][MX];

int main() {

    phi[0] = 0;
    phi[1] = 1;

    for (int p, i = 2; i < MX; i ++) {
        p = nextPrime[i];
        if (p) {
            if ((i/p)%p)
                phi[i] = phi[i/p]*(p-1);
            else
                phi[i] = phi[i/p]*p;
        } else {
            phi[i] = i-1;
            for (int j = i; j < MX; j += i) {
                nextPrime[j] = i;
            }
        }
    }


    for (int i = 0, u; i < MX; i ++) {
        u = i;
        while (u) {
            digcnt[u%10][i] ++;
            u /= 10;
        }
    }

    for (int i = 1, v; i < MX; i ++) {
        isAnagram[i] = true;
        v = phi[i];
        for (int j = 0; j < 10; j ++) 
            if (digcnt[j][i] != digcnt[j][v]) {
                isAnagram[i] = false;
                break;
            }

    }

    ans[1] = 0;
    ans[2] = 0;

    u64 lft, rgt;

    for (int i = 3, p, phi_p, phi_i; i < MX; i ++) {
        ans[i] = ans[i-1];
        if (isAnagram[i]) {
            
            p = ans[i];
            phi_p = phi[p];
            phi_i = phi[i];

            lft = (u64)i*phi_p;
            rgt = (u64)p*phi_i;

            if (lft < rgt) {
                ans[i] = i;
            } else if (lft == rgt) {
                ans[i] = i;
            }
        }
    }

    int t, n;
    scanf ("%d", &t);
    while (t--) {
        scanf("%d", &n);
        if (ans[n-1])
            printf("%lld\n", ans[n-1]);
        else 
            printf("No solution.\n");
    }


    return EXIT_SUCCESS;
}