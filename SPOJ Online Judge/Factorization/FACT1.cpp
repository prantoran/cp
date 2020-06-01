#include <bits/stdc++.h>
using namespace std;

__int128 in() {
	__int128 ret=0;
	string s;
	cin>>s;
	for(char c:s) {
		ret*=10;
		ret+=(c-'0');
	}
	return ret;
}

void out(__int128 x) {
	stack<char>s;
	while(x) {
		s.push((x%10 +'0'));
		x/=10;
	}
	while(!s.empty()) {
		cout<<s.top();
		s.pop();
	}
}

pair<__int128, int> factors[111];

long long mult(long long a, long long b, long long mod) {
    return (__int128)a * b % mod;
}

long long f(long long x, long long c, long long mod) {
    return (mult(x, x, mod) + c) % mod;
}

__int128 binpower(__int128 base, __int128 e, __int128 mod) {
    __int128 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = result * base % mod;
        base = base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(__int128 n, __int128 a, __int128 d, int s) {
    __int128 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool isPrimeMillerRabin(__int128 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    __int128 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

inline __int128 gcd ( __int128 a, __int128 b ) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while ( b ) { a = a % b; swap ( a, b ); } return a;
}


long long brent(long long n, long long x0=2, long long c=1) {
    long long x = x0;
    long long g = 1;
    long long q = 1;
    long long xs, y;

    int m = 128;
    int l = 1;
    while (g == 1) {
        y = x;
        for (int i = 1; i < l; i++)
            x = f(x, c, n);
        int k = 0;
        while (k < l && g == 1) {
            xs = x;
            for (int i = 0; i < m && i < l - k; i++) {
                x = f(x, c, n);
                q = mult(q, abs(y - x), n);
            }
            g = gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = gcd(abs(xs - y), n);
        } while (g == 1);
    }
    return g;
}

__int128 PollardRho(__int128 n) {
    if (n == 1) return 1;
    if (!(n%2)) return 2;


    srand(time(0));

    __int128 x = rand()%n + 1, c = rand()%n + 1;
    return brent(n, x, c);
}


__int128 findPrimeFactor(__int128 x) {
    __int128 y = x;
    while (!isPrimeMillerRabin(y)) y = PollardRho(x);
    return y;
}



const int MX = 11111111;
int primes[MX];
int pcnt;
bool sieve[MX];
void findPrimes(){
    primes[0]=2;
    pcnt=1;
    memset(sieve,0,sizeof(sieve));
    for(int i = 4;i<MX;i+=2)sieve[i]=1;
    for(int i = 3;i*i<=MX;i+=2)
        if(!sieve[i])
            for(int j = i*i;j<MX;j+=2*i){
                sieve[j]=1;
            }
 
    for(int i = 3;i<MX;i+=2)if(!sieve[i])primes[pcnt++]=i;
}

int main () {
    findPrimes();
    __int128 x, y, curp;
    int cnt, pdx;
    while (true) {
        x = in();
        if (!x) break;

        pdx = 0;

        for(int i = 0;i < pcnt; i++) {
             curp = primes[i];
            if(curp> x) break;
            if(!(x%curp)) {
                cnt=0;
                while(!(x%curp)) {
                    cnt++;
                    x/=curp;
                }

                factors[pdx++]={curp, cnt};
            }
        }

        while (x != 1) {
            y = findPrimeFactor(x);
            cnt = 0;
            while (!(x%y)) {
                x /= y;
                cnt ++;
            }

            factors[pdx++] = {y, cnt};
        }

        sort(factors, factors + pdx);
        for (int i = 0; i < pdx; i ++) {
            if (i) cout << " ";
            out(factors[i].first);
            cout << "^" << factors[i].second;
        } cout << "\n";
    }
}