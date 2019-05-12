// https://codingcompetitions.withgoogle.com/codejam/round/00000000000516b9/0000000000134cdf

#include <bits/stdc++.h>
using namespace std;

#define row first
#define col second

const int MUTATED = 3;
const int NOTFOUND = -1;

vector<string> a;

vector<vector<int> > b;

bool pure[20][20][20][20];

map<pair<pair<int, int>, pair<int, int> >,   int> dp;
map<pair<pair<int, int>, pair<int, int> >,  bool> dn;

int pdp[20][20], pdn[20][20];

vector<vector<int> > muRow, muCol;

int mex(const set<int>& s) {
    int ret = 0;
    while (s.count(ret)) ret ++;
    return ret;
}

int preplay(int r, int c) {
    
    if (r == 0 || c == 0) return 0;

    if (pdn[r][c]) return pdp[r][c];

    pdn[r][c] = 1;
    
    set<int> s;

    s.insert(preplay(r-1, c));

    for (int i =2; i < r; i ++) {
        s.insert(preplay(i-1, c) ^ preplay(r-i, c));
    }

    s.insert(preplay(r, c-1));

    for (int j = 2; j < c; j ++) {
        s.insert(preplay(r, j-1) ^ preplay(r, c-j));
    }

    return pdp[r][c] = mex(s);
}

void setPure(int r, int c) {
    memset(pure, 0, sizeof pure);

    for (int i1 = 0; i1 < r; i1 ++) {
        for (int i2 = i1; i2 < r; i2 ++) {
            for (int j1 = 0; j1 < c; j1 ++) {
                for (int j2 = j1; j2 < c; j2 ++) {
                    bool cur = 1;
                    if (b[i2][j2] == MUTATED) cur = 0;
                    if (i2 != i1) {
                        cur &= pure[i1][j1][i2-1][j2];
                    }
                    if (j2 != j1) {
                        cur &= pure[i1][j1][i2][j2-1];
                    }
                    pure[i1][j1][i2][j2] = cur;
                }
            }
        }
    }
}

void setMutatedRowCol(int r, int c) {
    muCol = vector<vector<int> > (c);
    muRow = vector<vector<int> > (r);

   
    for (int i = 0; i < r; i ++) {
        muRow[i] = vector<int> (c);
        if (b[i][0] == MUTATED) {
            muRow[i][0] = 0;
        } else {
            muRow[i][0] = NOTFOUND;
        }

        for (int j = 1; j < c; j ++) {
            muRow[i][j] = muRow[i][j-1];
            if (b[i][j] == MUTATED) {
                muRow[i][j] = j;
            }
        }
    }

    for (int j = 0; j < c; j ++) {
        
        muCol[j] = vector<int> (r);
        if (b[0][j] == MUTATED) {
            muCol[j][0] = 0;
        } else {
            muCol[j][0] = NOTFOUND;
        }        

        for (int i = 1; i < r; i ++) {
            muCol[j][i] = muCol[j][i-1];
            if (b[i][j] == MUTATED) {
                muCol[j][i] = i;
            }
        }
    }
}

bool isMutatedRow(int r, int cStart, int cEnd) {
    if (cStart > cEnd) return false;
    if (muRow[r][cEnd] >= cStart) return true;
    return false;
}

bool isMutatedCol(int c, int rStart, int rEnd) {

    if (rStart > rEnd) return false;

    if (muCol[c][rEnd] >= rStart) return true;

    return false;
}

int play(pair<int,int> tl, pair<int,int> br) {

    if (dn[{tl, br}]) return dp[{tl, br}];
    
    dn[{tl, br}] = 1;

    if (pure[tl.row][tl.col][br.row][br.col]) {
        return dp[{tl, br}] = preplay(br.row-tl.row+1, br.col-tl.col+1);
    }
    
    set <int> s;

    for (int i = tl.row; i <= br.row; i ++) {
        if (isMutatedRow(i, tl.col, br.col)) continue;

        if (i == tl.row) {
            s.insert(play({tl.row+1, tl.col}, br));
        } else if (i == br.row) {
            s.insert(play(tl, {br.row-1, br.col}));
        } else {
            int topPart = play(tl, {i-1, br.col});
            int botPart = play({i+1, tl.col}, br);
            s.insert(topPart ^ botPart);
        }
    }

    for (int j = tl.col; j <= br.col; j ++) {
        if (isMutatedCol(j, tl.row, br.row)) continue;

        if (j == tl.col) {
            s.insert(play({tl.row, tl.col+1}, br));
        } else if (j == br.col) {
            s.insert(play(tl, {br.row, br.col-1}));
        } else {
            int lftPart = play(tl, {br.row, j-1});
            int rgtPart = play({tl.row, j+1}, br);
            s.insert(lftPart ^ rgtPart);
        }
    }

    int ret = mex(s);

    return dp[{tl, br}] = ret;
}

int main() {
    
    freopen("data.in", "r", stdin);
    freopen("out1.txt", "w", stdout);
    
    for (int i = 1; i < 16; i ++) {
        for (int j = 1; j < 16; j ++) {
            pdp[i][j] = preplay(i, j);
        }
    }

    int t;
    cin >> t;

    for (int ca = 1; ca <= t; ca ++) {
        
        int r, c;
        cin >> r >> c;

        a = vector<string> (r);

        b = vector< vector<int> > (r);


        for (int i = 0 ; i < r; i ++) cin >> a[i];

        for (int i  = 0 ; i < r; i ++) {
            b[i] = vector<int> (c);
            for (int j = 0 ; j < c;  j ++) {
                if (a[i][j] == '#') b[i][j] = MUTATED;
            }
        }

        setPure(r, c);
     
        setMutatedRowCol(r, c);

        dn.clear();
        int ans = 0;

        for (int i = 0 ; i < r; i ++) {
            
            for (int j = 0 ; j < c; j ++) {
                
                if (b[i][j] == MUTATED) continue;
                
                if (!isMutatedRow(i, 0, c-1)) {

                    int nim = 0;

                    if (i-1 >= 0) {
                        nim ^= play({0, 0}, {i-1, c-1});
                    }

                    if (i+1 < r) {
                        nim ^= play({i+1, 0}, {r-1, c-1});
                    }

                    if (!nim) {
                        ans ++;
                    }
                }

                if (!isMutatedCol(j, 0, r-1)) {
                    int nim = 0;

                    if (j-1 >= 0) nim ^= play({0, 0}, {r-1, j-1});

                    if (j+1 < c) nim ^= play({0, j+1}, {r-1, c-1});
                    if (!nim) {
                        ans ++;
                    }
                }
            }
        }

        cout << "Case #" << ca << ": " << ans << "\n";
    }
   
    return 0;
}