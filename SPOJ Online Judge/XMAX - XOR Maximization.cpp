//SPOJ XMAXX
//https://www.hackerearth.com/notes/gaussian-elimination/
#include<bits/stdc++.h>
using namespace std;

#define ull unsigned long long
const int mxn = 111111;

int cntBits(ull n){
    int cnt = 0;
    while(n)cnt++,n>>=1;
    return cnt;
}
int n;
ull a[mxn];
int lengths[mxn];
vector<ull>buckets[65];
ull modifiedArray[111],idx=0;

int main(){
    //freopen("in.txt","r",stdin);
    cin>>n;
    for(int i =0 ;  i< n;i++){
        cin>>a[i];
    }

        for(int i = 0 ; i < n;i++)lengths[i]=cntBits(a[i]);
        for(int i = 0 ; i < 65;i++)buckets[i].clear();
        for(int i = 0 ;  i<n;i++)
            buckets[lengths[i]].push_back(a[i]);
        idx=0;
        for(int i = 64;i>=0;i--){
            if(buckets[i].size()){
                modifiedArray[idx++]=buckets[i][0];
                for(int j = 1,len=buckets[i].size();j<len;j++){
                    ull tmp = buckets[i][0]^buckets[i][j];
                    int ln =cntBits(tmp);
                    buckets[ln].push_back(tmp);
                }
            }
        }
        ull ans = 0;
        for(int i = 0 ; i<idx;i++){
            if(ans<(ans^modifiedArray[i])){
                ans ^=modifiedArray[i];
            }
        }

    cout<<ans<<"\n";
    return 0;
}

