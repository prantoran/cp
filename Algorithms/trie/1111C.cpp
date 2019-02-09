// https://codeforces.com/contest/1111/problem/C

#include<bits/stdc++.h>

#define LL long long

using namespace std;


LL pow2[32];

int n, k;

LL A, B;

LL a[200005];

int curlabel = 0;
const int trie_size=2;

class Trie{

    Trie *childs[trie_size];
    LL cnt;
    bool leaf;
    int label;

    public:
        Trie(){
            leaf = 0;
            cnt = 0;
            for(int i = 0 ; i < trie_size; i++ ) {
                childs[i]=NULL;
            }
            label = ++curlabel;
        }
        
        void add(LL num, int pp){
            
            cnt ++;

            if (pp < 0) {
                leaf = 1;
                return;
            }

            int child = 0;
            if (num & pow2[pp]) {
                child = 1;
            }
            
            if(childs[ child ] == NULL ) {
                childs[ child ] = new Trie();
            }

            int qq =pp - 1;

            return childs[child]->add(num, qq);
        }

        LL solve(int p) {

            if (leaf) {
                return cnt * B;
            }

            if (cnt == 0) {
                return A;
            }

            // cnt > 0
            LL ret = pow2[p] * B * cnt;

            LL lft = A, rgt = A;

            if (childs[0] != NULL) {
                lft = childs[0]->solve(p-1);
            }

            if (childs[1] != NULL) {
                rgt = childs[1]->solve(p-1);
            }

            ret = min(ret, lft + rgt);
            
            return ret;
        }
}*root;

int main() {
 
    pow2[0] = 1;
    for(int i = 1; i < 32; i ++) pow2[i] = pow2[i-1] * 2;

    root=new Trie();
    
    scanf("%d %d %lld %lld", &n, &k, &A, &B);

    for (int i = 0 ; i < k; i ++) {
        scanf("%lld", a + i);
        a[i] --;
    }

    sort(a, a + k);

    for (int i = 0 ; i < k; i ++) {
        root->add(a[i], n-1);
    }

    printf("%lld", root->solve(n));

	return 0;
}


