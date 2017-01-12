#include<bits/stdc++.h>
using namespace std;

const int mxn = 111;

int t,ca,len,to,so,sq,sz,tz,ans;
char S[mxn],T[mxn];
int mark[mxn];

queue<int>misone;
queue<int>miszero;
queue<int>misq1;
queue<int>misq0;

int main(){
    //freopen("in.txt","r",stdin);

    scanf("%d",&t);

    for(ca=1;ca<=t;ca++){
        scanf("%s",&S);
        scanf("%s",&T);
        len =strlen(S);

        so=0,to=0,sq=0,sz=0,tz=0;

            while(!misone.empty())misone.pop();
            while(!miszero.empty())miszero.pop();
            while(!misq1.empty())misq1.pop();
            while(!misq0.empty())misq0.pop();

            memset(mark,0,sizeof(mark));
            ans=0;

        printf("Case %d: ",ca);

        for(int i = 0 ; i < len;i++){
            if(T[i]=='1')to++;
            else tz++;
            if(S[i]=='1')so++;
            else if(S[i]=='?')sq++;
            else sz++;
            if(T[i]==S[i])mark[i]=1;
            else{
//                cout<<"\ten\n";
                if(S[i]=='1'){
                    misone.push(i);
                }
                else if(S[i]=='0'){
                    miszero.push(i);
                }
                else{
                    if(T[i]=='1')misq1.push(i);
                    else misq0.push(i);
                }
            }
        }

        while(!misone.empty() && !miszero.empty()){
            int pos1 = misone.front();
            misone.pop();
            int pos2 = miszero.front();
            miszero.pop();

            swap(S[pos1],S[pos2]);
            mark[pos1]=1;
            mark[pos2]=1;
            ans++;

        }

        if(misone.empty()){
            while(!miszero.empty()){
                int pos = miszero.front();
                miszero.pop();
                ans++;
                S[pos]='1';
                mark[pos]=1;
            }
        }
        else if(miszero.empty()){
            while(!misone.empty() && !misq1.empty()){
                int pos1 = misone.front();
                misone.pop();
                int pos2 = misq1.front();
                misq1.pop();
                S[pos2]='0';
                swap(S[pos1],S[pos2]);
                ans+=2;
                mark[pos1]=1;
                mark[pos2]=1;
            }
        }

        if(!misone.empty()){
            printf("-1\n");
            continue;
        }

        while(!misq1.empty()){
            ans++;
            misq1.pop();

        }
        while(!misq0.empty()){
            ans++;
            misq0.pop();

        }

        printf("%d\n",ans);

    }
    return 0;
}
