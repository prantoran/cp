// https://leetcode.com/problems/coin-change-ii

#define ll unsigned long long

int compareInts(const void * a, const void * b) {
    int valA = *(const int *)a;
    int valB = *(const int *)b;
    return (valA > valB) - (valA < valB);
}

int change(int amount, int* coins, int coinsSize) {
    qsort(coins, coinsSize, sizeof(int), compareInts);
    ll * dp = (ll *)calloc(amount + 1, sizeof(ll));
    dp[0] = 1;
    for (int j = coinsSize-1; j >= 0; j --) {
        int u = coins[j];
        for (int i = coins[j]; i <= amount; i ++) {
            dp[i] += dp[i-u];
        }
    }
    return (int)dp[amount];
}
