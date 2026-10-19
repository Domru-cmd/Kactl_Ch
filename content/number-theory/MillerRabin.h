/**
 * 作者:chilli, c1729, Simon Lindholm
 * 日期:2019-03-28
 * 许可:CC0
 * 来源:Wikipedia, https://miller-rabin.appspot.com/
 * 描述:确定性 Miller-Rabin 素性测试。
 * 保证对 $7 \cdot 10^{18}$ 以内的数正确;更大的数请用 Python 并随机扩展 A。
 * 时间:约 7 倍于 $a^b \mod c$ 的复杂度。
 * 状态:已对拍
 */
#pragma once

#include "ModMulLL.h"

bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n - 1), d = n >> s;

    for (ull a : A) { // ^ 计算末尾零的个数
        ull p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) {
            p = modmul(p, p, n);
        }
        if (p != n - 1 && i != s) return 0;
    }

    return 1;
}
