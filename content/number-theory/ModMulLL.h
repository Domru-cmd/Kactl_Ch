/**
 * 作者:chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * 日期:2019-04-24
 * 许可:CC0
 * 来源:https://github.com/RamchandraApte/OmniTemplate/blob/master/src/number_theory/modulo.hpp
 * 描述:对 $0 \le a, b \le c \le 7.2\cdot 10^{18}$ 计算 $a\cdot b\bmod c$(或 $a^b \bmod c$)。
 * 时间:\texttt{modmul} 为 O(1),\texttt{modpow} 为 O(\log b)
 * 状态:已对拍,正确性已证明
 * 细节:
 * 比朴素的 (__int128_t)a * b % M 快约 2 倍。
 * 正确性证明见 doc/modmul-proof.tex。更早版本(使用 a * b / (long double)M 时)的证明
 * 见 doc/modmul-proof.md。
 * 证明假设 long double 按 x87 80 位浮点实现;若为 64 位
 * (比如 MSVC 上),该实现仅在
 * $0 \le a, b \le c < 2^{52} \approx 4.5 \cdot 10^{15}$ 时有效。
 */
#pragma once

using ull = unsigned long long;

ull modmul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ull modpow(ull b, ull e, ull mod) {
    ull ans = 1;

    for (; e; b = modmul(b, b, mod), e /= 2) {
        if (e & 1) ans = modmul(ans, b, mod);
    }

    return ans;
}
