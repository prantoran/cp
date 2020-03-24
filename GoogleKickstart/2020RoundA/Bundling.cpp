// https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d3ff3

#include <bits/stdc++.h>
#define MX 200000
using namespace std;

class Node {
    public:
    Node* a[26];
    Node* b[26];
    int cnt, maxDepth, used;

    Node() {
        cnt = 0;
        maxDepth = 0;
    }

    void sum() {
        
        for (int i = 0; i < 26; i ++) {
            if (a[i] != NULL) {
                // cout << "\t\ta[" << (char)(i+'A') << "]->used:" << a[i]->used << endl;
                cnt -= a[i]->used;   
                used += a[i]->used;     
            }
        }

        
    }

    void sortDepth() {
        for (int i = 0; i < 26; i ++) {
            b[i] = a[i];
        }

        for (int i = 1; i < 26; i ++) {
            if (b[i] == NULL) continue;
            
            int j = i-1;
            if (j >= 0 && (b[j] == NULL || b[j]->cnt < b[j+1]->cnt)) {
                swap(b[j], b[j+1]);
                j--;
            }
        }
    }
    
};

class Trie {

    int ans;

    void dfs(Node *u, int k, int d) {

        if (u == NULL || u->cnt < k) return;
        
        u->sortDepth();

        for (int i = 0; i < 26; i ++) {
            Node *v = u->b[i];
            dfs(v, k, d+1);
        }

        u->sum();

        // cout << "u->cnt:" << u->cnt << endl;

        int groups = u->cnt / k; 
        ans += (groups*d);
        u->used += groups*k;

    }

    public:
    Node * root;
    
    Trie() {
        root = new Node();
    }

    void add(char * s) {
        int n = strlen(s);
        root->cnt ++;
        Node * u = root;

        for (int i = 0; i < n; i ++) {
            int c = s[i];
            int j = c- 'A';
            
            int curD = n-i;
            if (curD > u->maxDepth) {
                u->maxDepth = curD;
            }
            
            if (u->a[j] == NULL) {
                u->a[j] = new Node();
            }
            u = u->a[j];
            u->cnt ++;
            // cout << "c:" << (char)c << " cnt:" << u->cnt << endl;
        }


    }

    int solve(int k) {
        
        ans = 0;

        dfs(root, k, 0);

        return ans;
    }
};

char a[MX];

int main() {
    // freopen("data.in", "r", stdin);
    int ca, N, K;
    int t;
    scanf ("%d", &t);

    for (ca = 1; ca <= t; ca ++) {
        scanf("%d %d", &N, &K);

        Trie* trie = new Trie();

        for (int i = 0 ; i < N; i ++) {
            scanf ("%s", a);
            trie->add(a);
        }

        printf("Case #%d: %d\n", ca, trie->solve(K));

    }

    return 0;

}
