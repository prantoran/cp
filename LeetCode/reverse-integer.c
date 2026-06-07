// https://leetcode.com/problems/reverse-integer

// AUTHOR: Pinku Deb Nath

#define MXM 2147483648

bool check(const int * a, int sz, bool minus) {
    // 2147483648
    int b[] = {2, 1, 4, 7, 4, 8, 3, 6, 4, 8};
    if (sz > 10) {
        return false;
    } else if (sz < 10) {
        return true;
    }
    for (int i = 0; i < 10; i ++) {
        if (a[i] < b[i]) {
            return true;
        } else if (a[i] > b[i]) {
            return false;
        }
    }
    return minus; 
}

int reverse(int x){
    if (x == -MXM) {
        return false;
    }
    bool minus = false;
    if (x < 0) {
        minus = true;
    }
    int digits[11];
    int sz = 0;
    int tmp = x;
    if (minus) {
        tmp = -tmp;
    }
    while (tmp) {
        if (sz || tmp%10 > 0) {
            digits[sz] = tmp %10;
            sz ++;
        }
        tmp /= 10;
    }
    if (check(digits, sz, minus) == false) {
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < sz; i ++) {
        ans *= 10;
        ans += digits[i];
    }
    if (minus) {
        ans = -ans;
    }
    return ans;
}
