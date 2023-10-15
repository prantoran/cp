class Solution {

    vector<pair<int, int>> walls;
    int n;
    vector<vector<int>> dp;

    int dfs(int pos = 0, int bonus = 0) {
        
        if (pos == n) return 1e9;

        if ((walls[pos].second + bonus + 1) >= n) 
            return walls[pos].first;
        
        if (dp[pos][bonus] != -1) return dp[pos][bonus];

        int ans = dfs(pos+1, bonus);

        ans = min(
            ans,
            walls[pos].first + dfs(pos+1, bonus + walls[pos].second + 1)
        );

        return dp[pos][bonus] = ans;
    }

public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        n = cost.size();
        walls = vector<pair<int, int>>(n);
        
        for (int i = 0; i < n; i ++) {
            walls[i] = {cost[i], time[i]};
        }

        sort(walls.begin(), walls.end());

        dp = vector<vector<int>>(n,vector<int>(n, -1));

        return dfs();
    }
};
