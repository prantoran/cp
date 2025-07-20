class UnionFind {
public:
    UnionFind(int sz) : root(sz), rank(sz), c(sz) {
        for (int i = 0; i < sz; i++) {
            root[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x) {
        if (x == root[x]) {
            return x;
        }
        return root[x] = find(root[x]);
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;
            } else {
                root[rootY] = rootX;
                rank[rootX] += 1;
            }
            
            c --;
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
    
    int components() { return c; }

private:
    vector<int> root;
    vector<int> rank;
    int c;
};


class UnionFind {
public:
    vector<int> rank, root;
    UnionFind(int n): rank(n, 1), root(n) {
        iota(root.begin(), root.end(), 0);
    }
    int find(int u) {
        return root[u] == u ? u : root[u] = find(root[u]);
    }
    bool unionSet(int u, int v) {
        int ru = find(x), rv = find(y);
        if (ru == rv) return false;
        if (rank[ru] > rank[rv]) {
            root[rv] = ru;
        } else if (rank[ru] < rank[rv]) {
            root[ru] = rv;
        } else {
            root[ru] = rv;
            root[rv] ++;
        }
        return true;
    }
    bool isConnected(int u, int v) {
        return find(u) == find(v);
    }
};
