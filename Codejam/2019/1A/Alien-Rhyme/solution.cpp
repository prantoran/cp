#include <iostream>
#include <stack>
using namespace std;


class node {
    
    public:
    node* parent;
    node* children[26];
    int cnt;
    int used;
    int leaf;

    
    node() {
        this->parent = nullptr;
        this->cnt = 0;
        this->leaf = 0;
        this->used = 0;
        memset(this->children, NULL, sizeof this->children);
    }

    ~node() {
        // destructor
    }
};


class trie {
    public:
    node* root;

    trie() {
        this->root = new node();
    }

    void insert(string s) {
        node *cur =this->root;
        int n = s.length();
        for (int i = 0; i < n; i ++) {
            int id = s[i]-'A';
            if (cur->children[id] == nullptr) {
                cur->children[id] = new node();
                cur->children[id]->parent = cur;
            }

            cur->cnt ++;

            cur = cur->children[id];
        }
        
        cur->leaf ++;
    }

    int countPairs() {

        stack<node*> st;

        st.push(this->root);
        int ans = 0;

        while(!st.empty()) {
            node* cur = st.top();

            if (cur->cnt < 2) {
                continue;
            }

            bool fnd = false;

            for (int i = 0 ; i < 26; i ++) {
                node* child = cur->children[i];
                
                if (child == nullptr) continue;
                if (child->cnt < 2) continue;
                fnd = true;
                st.push(child);

            }

            if (!fnd) {
                ans += 2;
                cur->cnt -= 2;
                cur->parent->used += 2;
            }

        }
    }

};

int main() {
    freopen("data.in", "r", stdin);

    return 0;
}