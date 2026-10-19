/**
 * 作者:Simon Lindholm
 * 日期:2017-04-20
 * 许可:CC0
 * 来源:自己整理
 * 描述:一个容器,可以加入形如 kx+m 的直线,并查询某点 x 处的最大值。
 *  常用于动态规划(凸包技巧,convex hull trick)。
 * 时间:O(\log N)
 * 状态:已对拍
 */
#pragma once

struct Line {
    mutable ll k, m, p;

    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (若是 double,取 inf = 1/.0,div(a,b) = a/b)
    static const ll inf = LLONG_MAX;

    ll div(ll a, ll b) { // 向下取整的除法
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }

    void add(ll k, ll m) {
        auto z = insert({k, m, 0});
        auto y = z++;
        auto x = y;

        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) {
            isect(x, erase(y));
        }
    }

    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
