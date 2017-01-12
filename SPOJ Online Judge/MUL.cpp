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

const int MAXN = 144444;

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

void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
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
		res[i] = int (fa[i].real() + 0.5); //This will not work if fa[i] is negative
}


int n,S[MAXN];
vector<int>RR,SS,TT;
int mxval,M;

int t,lenA,lenB,lenT;
char A[MAXN],B[MAXN];
int carry;

int main(){
    //freopen("in.txt","r",stdin);
    
    scanf("%d ",&t);
    while(t--){
        scanf("%s %s",&A,&B);
        
        lenA=strlen(A);
        lenB=strlen(B);
        if(lenA==1 && A[0]=='0'){
            printf("0\n");
            continue;
        }
        if(lenB==1 && B[0]=='0'){
            printf("0\n");
            continue;
        }
        
        RR.clear(),SS.clear();
        
        
        for(int i = lenA-1 ; i >=0 ;i--){
            RR.push_back(A[i]-'0');
        }
        for(int i = lenB-1 ; i>=0;i--){
            SS.push_back(B[i]-'0');
        }
        multiply(RR,SS,TT);
        
        lenT=TT.size();
        
        carry=0;
        
        for(int i = 0; i <lenT-1;i++){
            TT[i]+=carry;
            carry = TT[i]/10;
            TT[i]%=10;
            
            
        }
        TT[lenT-1]+=carry;
        
        lenT--;
        while(TT[lenT]==0 && lenT>0)lenT--;
        for(;lenT>=0;lenT--){
            printf("%d",TT[lenT]);
        }
        printf("\n");
        
    }
    
    return 0;
}
