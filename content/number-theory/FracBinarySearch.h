/**
 * 作者:Lucian Bicsi, Simon Lindholm
 * 日期:2017-10-31
 * 许可:CC0
 * 描述:给定 $f$ 与 $N$,求满足 $f(p/q)$ 为真且 $p, q \le N$ 的
 * 最小分数 $p/q \in [0, 1]$。
 * 若 $f$ 找到精确解时可以抛异常,那样就可以去掉 $N$。
 * 用法:fracBS([](Frac f) { return f.p>=3*f.q; }, 10); // {1,3}
 * 时间:O(\log(N))
 * 状态:对 n <= 300 已对拍
 */
#pragma once

struct Frac { ll p, q; };

template <class F>
Frac fracBS(F f, ll N) {
    bool dir = 1, A = 1, B = 1;
    Frac lo{0, 1}, hi{1, 1}; // 把 hi 设为 1/0 可搜索 (0, N]
    if (f(lo)) return lo;
    assert(f(hi));

    while (A || B) {
        ll adv = 0, step = 1; // dir 为真时移动 hi,否则移动 lo
        for (int si = 0; step; (step *= 2) >>= si) {
            adv += step;
            Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
            if (abs(mid.p) > N || mid.q > N || dir == !f(mid)) {
                adv -= step;
                si = 2;
            }
        }
        hi.p += lo.p * adv;
        hi.q += lo.q * adv;
        dir = !dir;
        swap(lo, hi);
        A = B;
        B = !!adv;
    }

    return dir ? hi : lo;
}
