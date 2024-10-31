// https://leetcode.com/problems/construct-2d-grid-matching-graph-layout

class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        vector<vector<int>> G (n, vector<int>());
        for (const auto & e: edges) {
            G[e[0]].push_back(e[1]);
            G[e[1]].push_back(e[0]);
        }

        vector<int> degree(n);
        int deg1Node = -1, deg2Node = -1;
        for (int i = 0; i < n; i ++) {
            int sz = G[i].size();
            degree[i] = sz;
            if (sz == 1) {
                deg1Node = i;
            } else if (sz == 2) {
                deg2Node = i;
            }
        }

        if (deg1Node != -1) {
            vector<vector<int>> ans (1, vector<int>(n));
            ans[0][0] = deg1Node;
            int prev = -1, cur = deg1Node;
            for (int i = 1; i < n; i ++) {
                for (int u: G[cur]) {
                    if (u != prev) {
                        ans[0][i] = u;
                        prev = cur;
                        cur = u; 
                        break;
                    }
                }
            }
            return ans;
        }

        vector<int>firstRow;
        firstRow.push_back(deg2Node);
        vector<bool>visited(n, false);
        visited[deg2Node] = true;
        int cur = deg2Node;
        while(true) {
            int next = INT_MAX, cnt = INT_MAX;
            for (int u: G[cur]) {
                if (!visited[u] && degree[u] < cnt) {
                    cnt = degree[u];
                    next = u;
                }
            }
            firstRow.push_back(next);
            visited[next] = true;
            degree[cur] --;
            degree[next] --;
            if (degree[next] == 1) {
                break;
            }
            cur = next;
        }

        int cols = firstRow.size();
        int rows = n/cols;
        vector<vector<int>> ans(rows, vector<int>(cols));
        ans[0] = firstRow;
        for (int i = 1; i < rows; i ++) {
            for (int j = 0; j < cols; j ++) {
                int topNode = ans[i-1][j];
                for (int u: G[topNode]) {
                    if (!visited[u]) {
                        ans[i][j] = u;
                        visited[u] = true;
                        break;
                    }
                }
            }
        }

        return ans;
    }
};
