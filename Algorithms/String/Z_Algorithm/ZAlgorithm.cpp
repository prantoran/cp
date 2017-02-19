
#include <bits/stdc++.h>
using namespace std;



#define ZMAX 211111
#define Z_UNASSIGNED -1
class ZAlgorithm{
	/*
		Steps:
			1. Take input pattern P and searched string T
			2. Set ZSIZE, TSIZE
			3. Clear Z array
		Notes:
			The strings P and T are 0-based
			The Z array is 1-based
	*/
	public:
	char P[ZMAX],T[ZMAX];
	int Z[ZMAX];
	int ZSIZE;
	int PSIZE;

	ZAlgorithm(){}

	void clear_ZArray(){for(int i = 0 ; i <= ZSIZE;i++)Z[i] = Z_UNASSIGNED;}
	void preprocessZArray(){
		Z[0]=Z[1]=0; //Z[1] is 0 by default, because we cannot consider whole string
		int L=0,R = 0; //for kth iteration L and R points to l(k-1) and r(k-1) of previous iteration
		int beta;
		int k = 1,id,k2;
		while(k<ZSIZE && P[k-1]==P[k]){  // calculating Z[2]
			k++;
		}
		L = 2, R = k;
		Z[2] = R-L+1;
		for(k = 3; k <=ZSIZE;k++){
			if(k <= R){
				k2 = k - L + 1;
				beta = R - k + 1;


				if(Z[k2]<beta)Z[k] = Z[k2];
				else if(Z[k2]>beta)Z[k] = beta;
				else{ //Z[k2] == beta
					id = beta;
					while(R<ZSIZE && P[R] == P[id]){
						R ++; id ++;
					}
					L = k;
					Z[k] = R-L+1 ;
				}
			}else{
				id = k-1;
				k2 = 0;
				while(k2<ZSIZE && P[k2] == P[id]){
					id++;k2++;
				}
				L = k; R = id;
				Z[k] = R-L+1;
			}
		}
	}
	vector<int> findExactMatches(){
		PSIZE = strlen(P);
		strcat(P,"$");
		strcat(P,T);
		ZSIZE = strlen(P);
		preprocessZArray();

		vector<int>ret;

		for(int i = 1;i<=ZSIZE;i++){
			if(Z[i]==PSIZE)ret.push_back(i-PSIZE-1);
		}
		return ret;
	}
};

int main(){
	freopen("in.txt","r",stdin);
	ZAlgorithm a;
	cin>>a.P;
	cin>>a.T;
	//strcpy(a.T,"aabaabcaxaabaabcyxxyaabaabcaxaabaabcy");


	cout<<a.P<<endl;
	cout<<a.T<<endl;

	a.ZSIZE = strlen(a.P);
	a.clear_ZArray();
	a.preprocessZArray();
	
	vector<int>matches = a.findExactMatches();

	for(int i = 1  ; i <=a.ZSIZE;i++){
		cout<<a.Z[i]<<" ";
		cout<<"z["<<i<<"]:"<<a.Z[i]<<endl;
	}cout<<endl;
	cout<<"P:"<<a.P<<endl;
	for(auto u:matches){
		cout<<u<<endl;
	}
	return 0;
}


