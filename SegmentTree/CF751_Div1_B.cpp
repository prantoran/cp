
// https://codeforces.com/contest/1601/problem/B

#include <bits/stdc++.h>
#define MX 322222
#define INF 10000000
using namespace std;

int a[MX], b[MX];


class Node {
  public:
  int lazy, value;
  Node(int _value = -1, int _lazy = -1): value(_value), lazy(_lazy) {}
  void apply(int v) {
    lazy = max(lazy, v);
    value = max(value, v);
  }
  void reset() { lazy = -1; }
  void merge(const Node & a, const Node & b) {
    value = max(a.value, b.value);
  }
};

Node tree[4*MX];

void propagate(const int u, const int st, const int nd) {
  if (st == nd) return;
  tree[u*2].apply(tree[u].lazy);
  tree[u*2 + 1].apply(tree[u].lazy);
  tree[u].reset();
}

void update(const int u, const int st, const int nd, const int L, const int R, const int v) {
  propagate(u, st, nd);
  
  if (st > nd || L > R) return;
  if (st > R || nd < L) return;

  if (L <= st &&  nd <= R) {
    tree[u].apply(v);
    return;
  }


  int m = (st + nd) / 2;
  int l = 2*u;
  int r = l + 1;

  update(l, st, m, L, min(R, m), v);
  update(r, m+1, nd, max(L, m+1), R, v);
  tree[u].merge(tree[l], tree[r]);
}

int query(const int u, const int st, const int nd, const int L, const int R) {
  propagate(u, st, nd);
  if (st > R || nd < L) return -1;
  if (L > R || st > nd) return -1;
  if (L <= st && nd <= R) return tree[u].value;
  int m = (st + nd) / 2;
  return max(
    query(u*2, st, m, L, min(R, m)),
    query(u*2 + 1, m+1, nd, max(L, m+1), R)
  );
}

int main() {
  int n;
  scanf ("%d", &n);

  auto last = vector<int>(n+1, -1);

  for (int i = 1 ; i  <= n ;i ++) scanf ("%d", &a[i]);
  for (int i = 1 ; i  <= n ;i ++) {
    scanf ("%d", &b[i]);
    last[i+b[i]] = i;
  }

  for (int i = 1; i <= n; i ++) {
    update(1, 0, n, i - a[i], i, last[i]);
  }

  stack<int> ans;
  int cur = 0;
  while (cur != n) {
    ans.push(cur);
    cur = query(1, 0, n, cur, cur);
    if (cur == -1) { puts("-1"); return 0; }
  }

  printf("%d\n", (int)ans.size());
  while (!ans.empty()) {
    printf("%d ", ans.top());
    ans.pop();
  }
  
  return 0;
}
