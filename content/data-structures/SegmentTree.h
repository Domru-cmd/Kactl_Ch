/**
 * 作者:Lucian Bicsi
 * 日期:2017-10-31
 * 许可:CC0
 * 来源:民间流传
 * 描述:零下标最大线段树,区间左闭右开。
 * 可通过修改 T、f 和单位元来改变用途。
 * 时间:O(\log N)
 * 状态:已对拍
 */
#pragma once

struct Tree {
    using T = int;
    static constexpr T unit = INT_MIN;

    T f(T a, T b) { return max(a, b); } // 任意结合运算
    vector<T> s;
    int n;

    Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}

    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;) {
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
        }
    }

    T query(int b, int e) { // 查询区间 [b, e)
        T ra = unit, rb = unit;

        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }

        return f(ra, rb);
    }
};
