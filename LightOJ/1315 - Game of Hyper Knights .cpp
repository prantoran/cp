//http://lightoj.com/volume_showproblem.php?problem=1315
#include<bits/stdc++.h>
using namespace std;

template<class T>
inline T fi(){
    register char c = 0 ;
    register T a= 0;
    bool neg = false;
    while(c<33)c=getchar();
    while(c>33){
        if(c=='-')neg=true;
        else a=a*10+c-'0';
        c=getchar();
    }
    return neg?-a:a;
}

int t,n,pinku,ca,grundy[100010],x;
bool vis[100010];

char ans[16000];
char buffer[20];

int f(int x){
    if(vis[x])return grundy[x];
    vis[x]=1;
    int p=1;
    grundy[x]=0;
    for(;p<<1 <x;p++){
        if(!f(p)&&!f(x-p))grundy[x]=1;
    }


    return grundy[x];
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
    #endif

    ans[0]='\0';

    t = fi<int>();
    for(ca=1;ca<=t;ca++){

        n=fi<int>();
        pinku=0;
        while(n--){
            x=fi<int>();
            pinku^=f(x);
        }
        if(!pinku){
            sprintf(buffer,"Case %d: Bob\n",ca);
        }
        else{
            sprintf(buffer,"Case %d: Alice\n",ca);
        }
        strcat(ans,buffer);
    }
    printf("%s",ans);


    return 0;
}
