#include <bits/stdc++.h>
#define MX 100005

using namespace std;


vector<string> a;

map< pair<int,string>,  bool> dp;
map< pair<int,string>,  bool> dn;



vector<string> convertStr(const string& s, int c) {
    vector<string> ret;
    string cur = "";
    for (int i = 0, len = s.length(); i < len; i ++) {
        
        cur += s[i];

        if (i%c == (c-1)) {
            ret.push_back(cur);
            cur = "";
        }
    }

    return ret;
}

string toStr(const vector<string>& x) {
    string ret = "";
    for (auto u: x) {
        ret += u;
    }

    return ret;
}

char getTag(int turn) {
    if (turn == 0) return '0';
    else return '1';
}

vector<string> newGrid(const vector<string>& x) {
    vector<string> ret;
    for (auto u: x) {
        ret.push_back(u);
    }

    return ret;
}


pair<string, bool> playHorizontal(const vector<string>& x, char tag, int i, int j, int c) {
    
    auto y = newGrid(x);
    
    for (int k = j ; k < c; k ++) {
        char u = x[i][k];
        if (u == '#') {
            return {"", false};
        }
        if (u != '.') break;
        y[i][k] = tag;
    }

    for (int k = j -1 ; k>= 0; k --) {
        char u = x[i][k];
        if (u == '#') {
            return {"", false};
        }
        if (u != '.') break;
        y[i][k] = tag;
    }

    

    string ret = toStr(y);

    // cout << "horizontal i:" << i <<" j:" << j << " tag:" << tag << " ret:" << ret << endl;
    // printGrid(y);

    return {ret, true};
}


pair<string, bool> playVertical(const vector<string>& x, char tag, int i, int j, int r) {
    
    auto y = newGrid(x);
    
    for (int k = i ; k < r; k ++) {
        char u = x[k][j];
        if (u == '#') {
            return {"", false};
        }
        if (u != '.') break;
        y[k][j] = tag;
    }

    for (int k = i -1 ; k>= 0; k --) {
        char u = x[k][j];
        if (u == '#') {
            return {"", false};
        }
        if (u != '.') break;
        y[k][j] = tag;
    }

    string ret = toStr(y);

    // cout << "vertical i:" << i <<" j:" << j << " tag:" << tag << " ret:" << ret << endl;
    // printGrid(y);

    return {ret, true};
}

int ans;

bool play(int turn, string cur, int r, int c, bool first) {

    // cout <<"turn:" << turn <<" cur:" << cur << endl;

    if (dn[{turn, cur}]) return dp[{turn, cur}];
    dn[{turn, cur}] = 1;

    auto x = convertStr(cur, c);

    char tag = getTag(turn);

    bool ret = 0;
    if (turn == 1) ret = 1;

    bool fnd = 0;

    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            char u = x[i][j];
            if (u != '.') continue;

            auto move = playHorizontal(x, tag, i, j, c);
            if (move.second) {
                fnd = 1;
                bool nxtState = play(turn^1, move.first, r, c, false);

                if (turn == 0) ret |= nxtState;
                else ret &= nxtState;

                if (nxtState && first) {
					// cout << "(" << i << "," << j << ") --\n";

                    ans ++;
                }
                
            }

            move = playVertical(x, tag, i, j, r);
            if (move.second) {
                fnd = 1;
                bool nxtState = play(turn^1, move.first, r, c, false);
                
                if (turn == 0) ret |= nxtState;
                else ret &= nxtState;

                if (nxtState && first) {
					// cout << "(" << i << "," << j << ") |\n";
                    ans ++;
                }
                
            }
        }
    }

    if (!fnd && turn == 1) {
        ret = 1;
    }

    return dp[{turn, cur}] = ret;

}

int main() {
    
    freopen("data.in", "r", stdin);
    freopen("out2.txt", "w", stdout);
    
    int t;
    cin >> t;
    for (int ca = 1; ca <= t; ca ++) {
        
        int r, c;
        cin >> r >> c;

        a = vector<string> (r);

        dn.clear();

        for (int i = 0 ; i < r; i ++) cin >> a[i];

        // cout << "toStr:" << toStr(a) << "\n";

        // auto x = convertStr(toStr(a), c);
        // for (auto y: x) {
        //     cout << y << "\n";
        // }

        ans = 0;
        play(0, toStr(a), r, c, true);


        cout << "Case #" << ca << ": " << ans << "\n";
        
    }
   
    return 0;
}