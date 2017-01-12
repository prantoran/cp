/*
more than 4 times faster than simple
testing problem: UVA 12879
bitwise inversion permutation applied
recursive calls replaced with iterative
*/
 
#include<bits/stdc++.h>
#define PI 2*acos(0.0)
#define ll long long 
using namespace std;
 
const int MAXN = 644444;  
 
typedef complex<double> base;
 
typedef complex<double> base;
 
int rev (int num, int lg_n) {
	int res = 0;
	for (int i=0; i<lg_n; ++i)
		if (num & (1<<i))
			res |= 1<<(lg_n-1-i);
	return res;
}
 
 
void fft (vector<base> & a, bool invert) {
	int n = (int) a.size();
	
	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
	
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*PI/len * (invert ? -1 : 1);
		base wlen (cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w (1);
			for (int j=0; j<len/2; ++j) {
				base u = a[i+j],  v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}
 
/*
1. Build two different vectors with coefficient of the equation ( 3 + x + 2x^2 will be [3,1,2] )
2. Send them to multiply ( arr, brr, res )
3. res vector contains result of multiplication.
 
WARNING: FFT causes precision error. multiply() rounds them to integer.
*/
 
void multiply (const vector<ll> & a, const vector<ll> & b, vector<ll> & res) {
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
 
	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	fft (fa, true);
 
	res.resize (n);
	for (size_t i=0; i<n; ++i)
		res[i] = (ll)(fa[i].real() + 0.5); //This will not work if fa[i] is negative
}
 
 
vector<ll>RR,SS,TT;

int t,n;
ll val;
int main(){
   // freopen("in.txt","r",stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        n++;
        RR.clear();SS.clear();
        for(int i = 0;  i <n;i++){
            scanf("%lld",&val);
            RR.push_back(val);
        }
        reverse(RR.begin(),RR.end());
        
        for(int i = 0;  i <n;i++){
            scanf("%lld",&val);
            SS.push_back(val);
        }
        reverse(SS.begin(),SS.end());
        
        multiply(RR,SS,TT);
        
        for(int i=  2*n-2; i >=0;i--){
            
            printf("%lld",TT[i]);
            if(i)printf(" ");
        }printf("\n");
        
    }
    return 0;
}
