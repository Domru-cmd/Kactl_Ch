/**
 * 作者:Simon Lindholm
 * 日期:2015-03-20
 * 许可:CC0
 * 来源:自己整理
 * 描述:把 [from, to) 上的单调函数切分为最少的、取相同值的半开区间。
 *  对每个区间运行一次回调 g。
 * 用法:constantIntervals(0, sz(v), [\&](int x){return v[x];}, [\&](int lo, int hi, T val){...});
 * 时间:O(k\log\frac{n}{k})
 * 状态:已测试
 */
#pragma once

template <class F, class G, class T>
void rec(int from, int to, F &f, G &g, int &i, T &p, T q) {
    if (p == q) return;
    if (from == to) {
        g(i, to, p);
        i = to;
        p = q;
    } else {
        int mid = (from + to) >> 1;
        rec(from, mid, f, g, i, p, f(mid));
        rec(mid + 1, to, f, g, i, p, q);
    }
}

template <class F, class G>
void constantIntervals(int from, int to, F f, G g) {
    if (to <= from) return;
    int i = from;
    auto p = f(i), q = f(to - 1);
    rec(from, to - 1, f, g, i, p, q);
    g(i, to, q);
}
