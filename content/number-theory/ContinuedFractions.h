/**
 * 作者:Simon Lindholm
 * 日期:2018-07-15
 * 许可:CC0
 * 来源:Wikipedia
 * 描述:给定 $N$ 与非负实数 $x \ge 0$,求满足 $p, q \le N$ 的最佳有理近似 $p/q$。
 * 它将满足 $|p/q - x| \le 1/qN$。
 *
 * 对相邻的收敛项,$p_{k+1}q_k - q_{k+1}p_k = (-1)^k$。
 * ($p_k/q_k$ 在 $>x$ 与 $<x$ 之间交替。)
 * 若 $x$ 是有理数,$y$ 最终会变为 $\infty$;
 * 若 $x$ 是二次多项式的根,则各 $a$ 最终会呈循环。
 * 时间:O(\log N)
 * 状态:对 n <= 300 已对拍
 */
#pragma once

using d = double; // N ~ 1e7 时用 double;N ~ 1e9 时用 long double
pair<ll, ll> approximate(d x, ll N) {
    ll LP = 0, LQ = 1, P = 1, Q = 0, inf = LLONG_MAX;
    d y = x;

    for (;;) {
        ll lim = min(P ? (N - LP) / P : inf, Q ? (N - LQ) / Q : inf),
           a = (ll)floor(y), b = min(a, lim),
           NP = b * P + LP, NQ = b * Q + LQ;

        if (a > b) {
            // 若 b > a/2,存在给出更好近似的半收敛项;
            // 若 b = a/2,则可能有一个。
            // 这里返回 {P, Q} 可获得更规范的近似。
            return (abs(x - (d)NP / (d)NQ) < abs(x - (d)P / (d)Q)) ?
                make_pair(NP, NQ) : make_pair(P, Q);
        }
        if (abs(y = 1 / (y - (d)a)) > 3 * N) {
            return {NP, NQ};
        }
        LP = P;
        P = NP;
        LQ = Q;
        Q = NQ;
    }
}
