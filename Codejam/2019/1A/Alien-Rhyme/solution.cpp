// https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104e05

#include <iostream>
#include <stack>
#include <cstring>
#include <algorithm>

using namespace std;


class Node {
    
    public:
    Node* parent;
    Node* children[26];
    int cnt;
    int used;
    
    Node() {
        this->parent = nullptr;
        this->cnt = 0;
        this->used = 0;

        for (int i = 0 ; i < 26; i ++) 
            this->children[i] = nullptr;
    }
};


class Trie {
    public:
    Node* root;

    Trie() {
        this->root = new Node();

    }

    void insert(char *s) {
        Node *cur =this->root;
        int n = strlen(s);
        for (int i = 0; i < n; i ++) {
            int id = s[i]-'A';
            if (cur->children[id] == nullptr) {
                cur->children[id] = new Node();
                cur->children[id]->parent = cur;
            }

            cur = cur->children[id];
            cur->cnt ++;
        }
    }

    int countPairs(Node* cur) {

        if (cur->cnt < 2) return 0;

        int ret = 0;

        for (int i = 0 ; i < 26; i ++ ) {
            Node* child = cur->children[i];

            if (child == nullptr) continue;
            if (child->cnt < 2) continue;

            ret += countPairs(child);

            cur->used += child->used;
        }

        cur->cnt -= cur->used;

        if (cur->cnt >= 2) {
            ret += 2;
            cur->cnt -= 2;
            cur->used += 2;
        }

        return ret;
    }


    int solve() {
        int ret = 0;
        for (int i=  0; i < 26; i ++) {
            Node * child = this->root->children[i];
            if (child == nullptr) continue;
            ret += this->countPairs(child);
        }

        return ret;
    }

};

int main() {
    freopen("data.in", "r", stdin);

    int t;
    scanf("%d", &t);

    for (int ca = 1; ca <= t; ca ++) {

        Trie *trie = new Trie();

        char s[100];

        int n;
        scanf("%d ", &n);

        for (int i = 0 ; i < n; i ++) {
            scanf("%s", s);
            reverse(s, s + strlen(s));
            trie->insert(s);
        }

        int ans = trie->solve();

        printf("Case #%d: %d\n", ca, ans);
    }

    return 0;
}