#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int mxn = 1500;

int t;
ull a[mxn],ans[10];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    while(t--){
        for(int i = 0 ; i < mxn; i++)cin>>a[i];
        ull base = 1001;
        ull num = a[base-1];
        for(int i = 0 ; i< 7;i++){
            ans[i] = num%base;
            num-=ans[i];
            num/=base;
        }
        bool valid = 1;
        for(int i = 0 ; i< mxn && valid; i++){
            num = a[i];
            for(int j = 0 ; j < 7 && valid;j ++ ){
                num-=ans[j];
                if(num %(i+1)){
                    valid = false;
                }
                num/=(i+1);
            }
            if(num)valid = false;
        }
        if(valid){
            for(int i = 0 ; i < 7;i++){
                if(i)cout<<" ";
                cout<<ans[i];
            }cout<<endl;
        }
        else{
            cout<<"This is a smart sequence!\n";
        }
    }
    return 0;
}
