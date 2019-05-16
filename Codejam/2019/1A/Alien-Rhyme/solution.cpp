#include <iostream>
#include <stack>
using namespace std;


class node {
    
    public:

    node* children[26];
    int used;
    bool leaf;
    
    node() {
        this->used = 0;
        this->leaf = 0;
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
            }

            cur->used ++;

            cur = cur->children[id];
        }
        
        cur->leaf = true;
    }

    int countPairs() {

        stack<node*> st;

        st.push(this->root);
        int ans = 0;

        while(!st.empty()) {

        }
    }

};

int main() {
    freopen("data.in", "r", stdin);

    return 0;
}