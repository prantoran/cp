#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int id(char u) {
    return (int) (u - 'A'); 
}

char tag(int i) {
    return (char) (i + 'A');
}

vector<int> a;
vector<vector<int> > b;
vector<int> c;

int main() {
    // freopen("data.in", "r", stdin);
    int t, f;
    scanf("%d %d", &t, &f);

    for (int ca = 1; ca <= t; ca ++) {
        
        char u;
        
        a = vector<int> (5, 0);
        b = vector<vector<int> > (5);

        string ans = "";

        for (int i = 1; i <= 595; i += 5) {
            printf("%d\n", i);
            fflush(stdout);
            scanf(" %c", &u);

            a[id(u)] ++;
            b[id(u)].push_back(i);
        }

        int p[] = {23, 5, 1};

        for (int pi = 0; pi < 3; pi ++) {
            int cur = p[pi];

            int nid;

            for (int i = 0;  i < 5; i ++) {
                if (a[i] == cur) {
                    ans += tag(i);
                    nid = i;
                    break;
                }
            }

            c = vector<int> (b[nid].begin(), b[nid].end());
            a.clear();
            a = vector<int> (5, 0);
            b.clear();
            b = vector<vector<int> > (5);

            for (auto x: c) {
                int i = x + 1;
                printf("%d\n", i);
                fflush(stdout);
                scanf(" %c", &u);

                a[id(u)] ++;
                b[id(u)].push_back(i);
            }
        }

        for (int i = 0 ;  i < 5; i ++) {
            if (a[i] == 1) {
                printf("%d\n", b[i][0] + 1);
                fflush(stdout);
                scanf(" %c", &u);

                ans += u;
                ans += tag(i);
                break;
            }
        }

        printf("%s\n", ans.c_str());
        fflush(stdout);

        scanf(" %c", &u);
        if (u == 'N') break;

    }

    cerr << "everything ok\n";

    return 0;
}
