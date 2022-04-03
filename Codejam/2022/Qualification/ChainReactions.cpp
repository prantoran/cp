// https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a45ef7

#include <bits/stdc++.h>
using namespace std;


void dfsMin(
        const int node, 
        const vector<vector<int>> & G, 
        const vector<long long> & funs, 
        vector<long long> & minimum,
        vector<int> & minChild,
        vector<long long> & maximum) {
    
    maximum[node] = funs[node];

    if (!G[node].size()) {
        minimum[node] = funs[node];
        minChild[node] = node;
        return;
    }
    
    minimum[node] = INT_MAX;
    minChild[node] = -1;
    
    for (const auto & u: G[node]) {
        dfsMin(u, G, funs, minimum, minChild, maximum);
        if (minimum[node] >= maximum[u]) {
            minimum[node] = maximum[u];
            minChild[node] = u;
        }
    }
    
    if (maximum[node] <= maximum[minChild[node]]) {
        maximum[node] = maximum[minChild[node]];
    }
}


void dfs(
        const int node,
        const vector<vector<int>> & G, 
        const vector<long long> & funs, 
        const vector<long long> & minimum,
        const vector<int> & minChild,
        const vector<long long> & maximum,
        int type,
        long long & ans) {

    if (!type) 
        ans += maximum[node];
    
    if (!G[node].size()) return;
    
    dfs(minChild[node], G, funs, minimum, minChild, maximum, 1, ans);
    
    for (const auto & u: G[node]) {
        if (u != minChild[node]) {
            dfs(u, G, funs, minimum, minChild, maximum, 0, ans);
        } 
    }
}


int findParent(
        const int node, 
        const vector<bool> & alive,
        vector<int> & parent) { 
    
    if (alive[node]) return node;
    return parent[node] = findParent(parent[node], alive, parent);
}


int main() {
    int t, n;
    scanf ("%d", &t);
    for (int ca = 1; ca <= t; ca ++) {
        scanf ("%d", &n);
        // cout << "n:" << n << "\n";
        auto funs = vector<long long>(n+1);
        for (int i = 1; i <= n; i ++) {
            scanf ("%lld", &funs[i]);
        }
        
        auto parent = vector<int> (n+1, 0);
        auto children = vector<int> (n+1, 0);
        auto alive = vector<bool> (n+1, true);
        for (int i = 1; i <= n; i ++) {
            scanf ("%d", &parent[i]);
            children[parent[i]] ++;
        }
        
        // for (int i = 1; i <= n; i ++) {
        //     if (alive[i] && !children[i]) {
        //         int u = i;
        //         int p = parent[i];
        //         auto st = stack<int>();
        //         cout << "processing :" <<i << "\n";
        //         while (p) {
        //             cout << "\tlooping over u:" << u << "\tp:" << p << "\n";
        //           while (p && children[p] == 1) {
        //               st.push(u);
        //               alive[u] = false;
        //               funs[p] = max(funs[u], funs[p]);
        //               u = p;
        //               p = parent[u];
        //           }

        //           cout << "\t\tbranching parent:" << p << "\n";
                  
        //           while (!st.empty()) {
        //               const auto v = st.top();
        //               st.pop();
        //               parent[v] = p;
        //           }

        //           u = p;
        //           p = parent[u];
        //           if (p) {
        //               u = p;
        //               p = parent[u];
        //           }
        //         }
        //     }
        // }
        
        auto G = vector<vector<int>> (n+1, vector<int>());
        for (int i = 1; i <= n; i ++) {
            if (alive[i]) {
                G[findParent(parent[i], alive, parent)].push_back(i);    
            }
        }
        
        auto minimum = vector<long long> (n+1, INT_MAX);
        auto minChild = vector<int> (n+1, 0);
        auto maximum = vector<long long> (n+1, INT_MIN);
        dfsMin(0, G, funs, minimum, minChild, maximum);
        

        long long ans = 0;
        for (const auto & u: G[0]) {
            dfs(u, G, funs, minimum, minChild, maximum, 0, ans);
        }
        
        printf("Case #%d: %lld\n", ca, ans);    
        
    }
}
