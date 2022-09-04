
#include <bits/stdc++.h>
#define SZ 12
using namespace std;


class Customer {
    public:
    int x, y, c;

    Customer() {}

    Customer(int x, int y, int c) {
        this->x = x;
        this->y = y;
        this->c = c;
    }
};


int customerMask(int id) {
    return (1 << (id-1));
}


long long dp[SZ][SZ][30][1<<10];
int dn[SZ][SZ][30][1<<10];


// North, East, West, South
int dx[] = {0, 1, -1, 0};
int dy[] = {-1, 0, 0, 1};


long long evaluate(long long c, char op, int toll) {
    long long ans = 0;
    if (op == '+') ans = c + toll;
    else if (op == '-') ans = c - toll;
    else if (op == '*') ans = c * toll;
    else {
        if (c < 0) {
            long long d = -c/toll;
            if (c%toll) d ++;
            ans = -d;
        } else {
            ans = c/toll;
        }
    }

    return ans;
}


int main() {
    int T, N, P, M, Ar, Ac;
    
    char op[4];
    int toll[4];

    int grid[SZ][SZ];

    Customer customers[SZ];

    scanf ("%d", &T);    
    for (int ca = 1; ca <= T; ca ++) {
        scanf ("%d %d %d %d %d\n", &N, &P, &M, &Ar, &Ac);

        // North, East, West, South
        for (int i = 0; i < 4; i ++) {
            scanf("%c %d\n", &op[i], &toll[i]);
        }

        for (int i = 0 ; i<= N; i ++)
            for (int j = 0; j <= N; j ++)
                grid[i][j] = 0;

        for (int i = 0; i < P; i ++) {
            scanf("%d %d %d", &customers[i].x, &customers[i].y, &customers[i].c);
            grid[customers[i].x][customers[i].y] = i + 1; 
        }

        dn[Ar][Ac][0][0] = ca;
        dp[Ar][Ac][0][0] = 0;

        for (int t = 1; t <= M; t ++) {
            for (int i = 1; i <= N; i ++) {
                for (int j = 1; j <= N; j ++) {
                    for (int p = 0; p < (1 << P); p ++) {
                        if (dn[i][j][t-1][p] == ca) {
                            dn[i][j][t][p] = ca;
                            dp[i][j][t][p] = dp[i][j][t-1][p];
                        }

                        if (grid[i][j]) {
                            int mask = customerMask(grid[i][j]);
                            if (p & mask) { // valid combination
                                if (dn[i][j][t-1][p^mask] == ca) {
                                    long long cusCur = dp[i][j][t-1][p^mask] + customers[grid[i][j]-1].c;
                                    if (dn[i][j][t][p] == ca) {
                                        dp[i][j][t][p] = max(dp[i][j][t][p], cusCur);
                                    } else {
                                        dn[i][j][t][p] = ca;
                                        dp[i][j][t][p] = cusCur;
                                    }
                                }
                            }
                        }

                        for (int k = 0; k < 4; k ++) {
                            int ni = i - dy[k];
                            int nj = j - dx[k];

                            if (dn[ni][nj][t-1][p] == ca) {
                                long long cur = evaluate(dp[ni][nj][t-1][p], op[k], toll[k]);
                                if (dn[i][j][t][p] == ca) {
                                    dp[i][j][t][p] =max(dp[i][j][t][p], cur);
                                } else {
                                    dn[i][j][t][p] = ca;
                                    dp[i][j][t][p] = cur;
                                }
                            }

                            if (grid[i][j]) {
                                int mask = customerMask(grid[i][j]);
                                if (p & mask) {                                    
                                    if (dn[ni][nj][t-1][p^mask] == ca) {
                                        long long cusCur = customers[grid[i][j]-1].c + evaluate(dp[ni][nj][t-1][p^mask], op[k], toll[k]);
                                                                                
                                        if (dn[i][j][t][p] == ca) {
                                            dp[i][j][t][p] = max(dp[i][j][t][p], cusCur);
                                        } else {
                                            dn[i][j][t][p] = ca;
                                            dp[i][j][t][p] = cusCur;
                                        }
                                    }
                                }
                            }
                        }
                    }           
                }
            }
        }

        bool found = false;
        int fullMask = (1 << P) - 1;
        long long ans;
        for (int i = 1; i <= N; i ++) {
            for (int j = 1; j <= N; j ++) {
                if (dn[i][j][M][fullMask] == ca) {
                    if (found) {
                        ans = max (ans, dp[i][j][M][fullMask]);
                    } else {
                        found = true;
                        ans = dp[i][j][M][fullMask];
                    }
                }
            }
        }

        printf("Case #%d: ", ca);
        if (found) printf("%lld\n", ans);
        else printf("IMPOSSIBLE\n");
    }
 }
