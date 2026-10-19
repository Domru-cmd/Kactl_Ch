/**
 * 作者:Lucian Bicsi
 * 日期:2017-10-31
 * 许可:CC0
 * 来源:Wikipedia
 * 描述:从前 $2n$ 项恢复任意 $n$ 阶线性递推关系。
 * 适合在暴力求出前几项后猜线性递推。
 * 在任何域上都应可用,但不保证浮点的数值稳定性。
 * 输出大小 $\le n$。
 * 用法:berlekampMassey({0, 1, 1, 3, 5, 11}) // {1, 2}
 * 时间:O(N^2)
 * 状态:在模 5 下对 n <= 5 与所有 s 已暴力验证
 */
#pragma once

#include "../number-theory/ModPow.h"

vector<ll> berlekampMassey(vector<ll> s) {
    int n = (int)s.size(), L = 0, m = 0;
    vector<ll> C(n), B(n), T;
    C[0] = B[0] = 1;

    ll b = 1;
    for (int i = 0; i < n; i++) {
        m++;
        ll d = s[i] % mod;
        for (int j = 1; j < L + 1; j++) d = (d + C[j] * s[i - j]) % mod;
        if (!d) continue;
        T = C;
        ll coef = d * modpow(b, mod - 2) % mod;
        for (int j = m; j < n; j++) C[j] = (C[j] - coef * B[j - m]) % mod;
        if (2 * L > i) continue;
        L = i + 1 - L;
        B = T;
        b = d;
        m = 0;
    }

    C.resize(L + 1);
    C.erase(C.begin());
    for (ll &x : C) x = (mod - x) % mod;
    return C;
}
