/**
 * 作者:Simon Lindholm
 * 日期:2016-08-31
 * 许可:CC0
 * 来源:http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * 描述:求模平方根的 Tonelli-Shanks 算法。求 $x$ 使 $x^2 = a \pmod p$($-x$ 是另一解)。
 * 时间:最坏 O(\log^2 p),对多数 $p$ 为 O(\log p)
 * 状态:对所有 a,p <= 10000 已测试
 */
#pragma once

#include "ModPow.h"

ll sqrt(ll a, ll p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0) return 0;
    assert(modpow(a, (p - 1) / 2, p) == 1); // 否则无解
    if (p % 4 == 3) return modpow(a, (p + 1) / 4, p);

    // 若 p % 8 == 5,a^(n+3)/8 或 2^(n+3)/8 * 2^(n-1)/4 也可行
    ll s = p - 1, n = 2;
    int r = 0, m;

    while (s % 2 == 0) {
        r++;
        s /= 2;
    }
    /// 找一个模 p 的非二次剩余
    while (modpow(n, (p - 1) / 2, p) != p - 1) {
        n++;
    }

    ll x = modpow(a, (s + 1) / 2, p);
    ll b = modpow(a, s, p), g = modpow(n, s, p);

    for (;; r = m) {
        ll t = b;
        for (m = 0; m < r && t != 1; m++) {
            t = t * t % p;
        }
        if (m == 0) return x;
        ll gs = modpow(g, 1LL << (r - m - 1), p);
        g = gs * gs % p;
        x = x * gs % p;
        b = b * g % p;
    }
}
