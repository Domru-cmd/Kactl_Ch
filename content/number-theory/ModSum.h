/**
 * 作者:Simon Lindholm
 * 日期:2015-06-23
 * 许可:CC0
 * 来源:自己整理
 * 描述:取模等差数列的求和。
 *
 * \texttt{modsum(to, c, k, m)} = $\sum_{i=0}^{\mathrm{to}-1}{(ki+c) \% m}$。
 * \texttt{divsum} 类似,但用于向下取整除法。
 * 时间:$\log(m)$,常数较大。
 * 状态:对所有 |k|,|c|,to,m <= 50 已测试,并在 kattis:aladin 上通过
 */
#pragma once

using ull = unsigned long long;

ull sumsq(ull to) { return to / 2 * ((to - 1) | 1); }
/// ^ 故意写成这样,以正确处理溢出

ull divsum(ull to, ull c, ull k, ull m) {
    ull res = k / m * sumsq(to) + c / m * to;
    k %= m;
    c %= m;
    if (!k) return res;
    ull to2 = (to * k + c) / m;
    return res + (to - 1) * to2 - divsum(to2, m - 1 - c, m, k);
}

ll modsum(ull to, ll c, ll k, ll m) {
    c = ((c % m) + m) % m;
    k = ((k % m) + m) % m;
    return to * c + k * sumsq(to) - m * divsum(to, c, k, m);
}
