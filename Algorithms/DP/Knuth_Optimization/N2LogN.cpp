void solve(vlong level, vlong pBegin, vlong pEnd, vlong sBegin, vlong sEnd) {
    if (pBegin > pEnd) return;
    vlong md = (pBegin+pEnd)/2;
    vlong ss = sBegin;
    vlong ee = MIN(sEnd, md-1);
    dp[md][level] = mod * mod;
    for (vlong i=ss; i<=ee; i++) {
        vlong v = dp[i][level-1] + C[i+1][md];
        if (dp[md][level] > v) {
            dp[md][level] = v;
            A[md][level] = i;
        }
    }
    vlong sNow = A[md][level];
    solve(level,pBegin,md-1,sBegin,sNow);
    solve(level,md+1,pEnd,sNow,sEnd);
}
