/**
 * 作者:Simon Lindholm
 * 日期:2019-05-22
 * 许可:CC0
 * 描述:中国剩余定理。
 *
 * \texttt{crt(a, m, b, n)} 计算满足 $x\equiv a \pmod m$、$x\equiv b \pmod n$ 的 $x$。
 * 若 $|a| < m$ 且 $|b| < n$,则所得 $x$ 满足 $0 \le x < \text{lcm}(m, n)$。
 * 假设 $mn < 2^{62}$。
 * 时间:$\log(n)$
 * 状态:可用
 */
#pragma once

#include "euclid.h"

ll crt(ll a, ll m, ll b, ll n) {
    if (n > m) {
        swap(a, b);
        swap(m, n);
    }
    ll x, y, g = euclid(m, n, x, y);
    assert((a - b) % g == 0); // 否则无解
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m * n / g : x;
}
