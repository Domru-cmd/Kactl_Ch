/**
 * 作者:佚名
 * 日期:2002-09-15
 * 来源:早于 tinyKACTL
 * 描述:求整数 $x$ 与 $y$,使 $ax+by=\gcd(a,b)$。
 * 若只需要 gcd,请改用内置的 \texttt{\_\_gcd}。
 * 若 $a$ 与 $b$ 互素,则 $x$ 是 $a \pmod{b}$ 的逆元。
 */
#pragma once

ll euclid(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}
