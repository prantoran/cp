#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;

template<class T>
inline T gcd(T a,T b){
    a=abs(a);
    b=abs(b);
    while(b) b ^= a ^= b ^= a %= b;
    return a;
}

const ll mxn = 11111111;
ll primes[mxn];
int pcnt;
bool sieve[mxn];
void findPrimes(){
    primes[0]=2;
    pcnt=1;
    memset(sieve,0,sizeof(sieve));
    for(ll i = 4;i<mxn;i+=2)sieve[i]=1;
    for(ll i = 3;i*i<=mxn;i+=2)
        if(!sieve[i])
            for(ll j = i*i;j<mxn;j+=2*i){
                sieve[j]=1;
            }

    for(ll i = 3;i<mxn;i+=2)if(!sieve[i])primes[pcnt++]=i;
}

//--------------------------POLLARD RHO--------------------------------

template<class T>
T mulmod(T a,T b,T c){
    T x = 0, y = a%c;
    while(b > 0){
        if( b%2 == 1 ){
            x = (x+y)%c;
        }
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}

template<class T>
T modulo(T a, T b,T c){
    T x = 1, y = a;
    while(b > 0){
        if( b%2 == 1) {
            x = mulmod(x,y,c);
        }
        y = mulmod(y,y,c);
        b /= 2;
    }
    return x%c;
}

template<class T>
bool Miller(T p, int iteration){
    if(p<2)return false;
    if(p!=2 && p%2==0)return false;
    T s = p -1;
    while(s%2==0)s/=2;
    for(int i = 0 ; i < iteration;i++){
        T a = rand()%(p-1)+1,temp=s;
        T mod = modulo<T>(a,temp,p);
        while( temp!=(p-1) && mod!=1 && mod!=(p-1) ){
            mod = mulmod<T>(mod,mod,p);
            temp *= 2;
        }
        if(mod!=(p-1) && temp%2==0)return false;
    }
    return true;
}

template<class T>
T PollardRho(T n){
    srand(time(NULL));
    if(n==1)return n;
    if(n%2 == 0)return 2;
    if(Miller<T>(n,50))return n;
    T x = (rand()%(n-2))+2;
    T y = x;
    T c = (rand()%(n-1))+1;
    T d = 1;
    while(d==1){
        x = (modulo<T>(x,2,n)+c+n)%n;
        y = (modulo<T>(y,2,n)+c+n)%n;
        y = (modulo<T>(y,2,n)+c+n)%n;

        d = gcd<ll>(abs(x-y), n);
        if(d==n)return PollardRho(n);
    }
    return d;
}

//--------------------------POLLARD RHO END-----------------------------

ll n,factors[111],A;
int fcnt[111],pdx,cnt;
map<ll,int>largefid;
int nid[111];

int main(){
    //freopen("in.txt","r",stdin);
    findPrimes();
    while(cin>>n){
        if(n==0)break;
        pdx=0;
        for(int i = 0 ;  i<pcnt;i++){
            ll curp = primes[i];
            if(curp>n)break;
            if(!(n%curp)){
                cnt=0;
                while(!(n%curp)){
                    cnt++;
                    n/=curp;
                }
                factors[pdx]=curp;
                fcnt[pdx++]=cnt;
            }
        }
        largefid.clear();
        while(n!=1){
            A=PollardRho(n);
            cnt=0;
            while(!(n%A)){
                cnt++;
                n/=A;
            }
            fcnt[pdx]=cnt;
            factors[pdx++]=A;

        }
        for(int i = 0 ; i < pdx;i++)nid[i]=i;
        sort(nid,nid+pdx,[](int aa,int bb){
                return factors[aa]<factors[bb];
            });
        for(int i = 0 ;  i < pdx;i++){
            if(i)printf(" ");
            printf("%lld",factors[nid[i]]);
            printf("^");
            printf("%d",fcnt[nid[i]]);
        }printf("\n");

    }
    return 0;
}
