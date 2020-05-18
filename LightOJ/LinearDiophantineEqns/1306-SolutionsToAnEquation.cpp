#include <iostream>
#define LL long long
using namespace std;
LL gcd(LL a, LL b, LL& x, LL& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL x1, y1;
    LL d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(LL a, LL b, LL c, LL &x0, LL &y0, LL &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift_solution(LL & x, LL & y, LL a, LL b, LL cnt) {
    x += cnt * b;
    y -= cnt * a;
}


LL find_all_solutions(LL a, LL b, LL c, LL minx, LL maxx, LL miny, LL maxy) {

    if (!a) {
        if (!b) {
            if (c == 0) {
                return (maxx-minx+1)*(maxy-miny+1);
            } else {
                return 0;
            }
        } else {
            if (c%b) return 0;
            c = c/b;
            if (c >= miny && c <= maxy) return (maxx-minx+1);
            else return 0;
        }
    } else if(!b) {
        if (c%a) return 0;
            c = c/a;
            if (c >= minx && c <= maxx) return (maxy-miny+1);
            else return 0;
    }

    LL x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    LL sign_a = a > 0 ? +1 : -1;
    LL sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    LL lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    LL rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    LL lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    LL rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    LL lx = max(lx1, lx2);
    LL rx = min(rx1, rx2);

    if (lx > rx)
        return 0;
    return (rx - lx) / abs(b) + 1;
}

int main() {

    int t;
    LL A, B, C;
    
    LL x1, x2, y1, y2;

    scanf ("%d", &t);
    for (int ca = 1; ca <= t; ca ++) {
        scanf ("%lld %lld %lld %lld %lld %lld %lld", &A, &B, &C, &x1, &x2, &y1, &y2);
        
        printf("Case %d: %lld\n", ca, find_all_solutions(A, B, -C, x1, x2, y1, y2));
    
    }
    

    return 0;
}