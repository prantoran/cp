#include<bits/stdc++.h>
#define PI 2*acos(0.0)
using namespace std;

const int MAXN = 444444;

typedef complex<double> base;

typedef complex<double> base;

void fft (vector<base> & a, bool invert) {
	int n = (int) a.size();
	if (n == 1)  return;

	vector<base> a0 (n/2),  a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i+1];
	}
	fft (a0, invert);
	fft (a1, invert);

	double ang = 2*PI/n * (invert ? -1 : 1);
	base w (1),  wn (cos(ang), sin(ang));
	for (int i=0; i<n/2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i+n/2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2,  a[i+n/2] /= 2;
		w *= wn;
	}
}

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
		res[i] = int (fa[i].real() + 0.5);
}


int n,S[MAXN];
vector<int>SS,TT;
int mxval,M;
int main(){
//freopen("in.txt","r",stdin);
    while(scanf("%d",&n)!=EOF){
        memset(S,0,sizeof(S));
        mxval=1;
        SS.clear();
        for(int i = 0 , val;i<n;i++){
            scanf("%d",&val);
            S[val]=1;
            mxval=max(mxval,val);
        }
        mxval++;
        SS.push_back(1);
        for(int i = 1 ; i < 2*(mxval+1);i++){
            if(S[i])SS.push_back(1);
            else SS.push_back(0);
        }


        multiply(SS,SS,TT);

//        for(int i = 0 , len=TT.size();i<len;i++){
//            cout<<"i:"<<i<<"\tval:"<<TT[i]<<endl;
//        }
        int ans = 0;
        scanf("%d",&M);
        for(int val,i = 0 ; i < M;i++){
            scanf("%d",&val);
            if(TT[val]>0)ans++;
        }

        printf("%d\n",ans);
    }
    return 0;
}
