
// #pragma comment(linker, "/STACK:16777216")

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")

// #include <bits/stdc++.h>

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<vector>
#include<deque>
#include<functional>
#include<string>
#include<iostream>
#include<cctype>
#include<set>
#include<climits>
#include<iomanip>
#include<cassert>
#include<sstream>
// #include <bits/stdtr1c++.h>
// #include <sys/socket.h>
// #include <sys/types.h> 

using namespace std;

#define UMAP unordered_map
#define USET unordered_set

#define eb emplace_back
#define mt make_tuple
#define fbo find_by_order
#define ook order_of_key

#define DBG(x) cout << #x << " = " << x << endl
#define RAN(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))
#define EPS 1e-9

#define ABS(x) ((x)<0?-(x):(x))
#define UNIQUE(z) z.erase(unique(z.begin(), z.end()), z.end())

const long long INF = 1e18;
const double E = 2.71828182845904523536;
const double GAMMA = 0.5772156649;
// const long long MOD = 1000000007; // 998244353 1000000009
const long double PI = acosl(-1);
const long long LMAX = 9223372036854775800LL;


using LL = long long; 
using LD  = long double;
// typedef vector<int> vi;
using vi = vector<int>;
using ii = pair<LL,LL>;





namespace mindivisors {

const int N = 10 * 1000 * 1000  + 11;

int mind[N];

void buildSieve() {
    vector<int> pr;

    mind[0] = mind[1] = 1;

    for (int i = 2; i < N; i ++) {
        if (mind[i] == 0) {
            mind[i] = i;
            pr.push_back(i);
        }
        for (int j = 0, ln = pr.size(); j < ln && pr[j] <= mind[i] && i*pr[j] < N; j ++) {
            mind[i*pr[j]] = pr[j];
        }
    }
}

}


template<typename T>
ostream& operator<<(ostream& out, vector<T> v) {
    out<<"[ ";

    for(int i = 0, len = v.size(); i < len; i ++ ) {
        if(i) out<<", ";
        out<<v[i];
    }

    out<<" ]";
    return out;
}

template<typename T1, typename T2>
ostream& operator<<(ostream &out, pair<T1, T2> p)
{
    out<<"( "<<p.first<<", "<<p.second<<")";
    return out;
}

template<typename T>
ostream& operator,(ostream &out, T x)
{
    out<<x<<" ";
    return out;
}


template <typename T>
struct Point{
    T x, y;
    
    inline Point() {}
    Point(T _x, T _y) : x(_x), y(_y) {}

    inline bool operator < (const Point& other) const{
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }

    friend ostream& operator<<(ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

#define _DEBUG

#define MX 200000
int t, k;
int n;
int c[MX], d[MX];


int main() {

    #ifdef _DEBUG
        freopen("data.in", "r", stdin);
        //freopen("out.txt", "w", stdout);  
   	    double start_time = clock();
    #endif

    scanf ("%d", &t);

    for (int ca = 1; ca <= t; ca ++) {
        scanf("%d %d", &n, &k);

        for (int i = 0 ; i < n; i ++) scanf ("%d", &c[i]);
        for (int i = 0 ; i < n; i ++) scanf ("%d", &d[i]);


        int ans = 0;

        for (int i = 0 ; i < n ; i++) {
            for (int j = i ; j < n; j ++) {
                int x = c[i];
                int y = d[i];

                for (int p = i ; p <= j; p ++) {
                    x = max(x, c[p]);
                    y = max(y, d[p]);
                }

                if (abs(x-y) <= k) ans ++;
            }
        }

        printf("Case #%d: %d\n", ca, ans);
    }




    
    #ifdef _DEBUG
        double end_time = clock();
        double val = (end_time-start_time)/CLOCKS_PER_SEC;
        fprintf(stderr, "Time = %lf\n", val);
        cerr << "\nTIME = " << val << endl;
    #endif




    // return 0;
    exit(0); 
}