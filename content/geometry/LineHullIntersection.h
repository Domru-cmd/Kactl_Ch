/**
 * 作者:Oleksandr Bacherikov, chilli
 * 日期:2019-05-07
 * 许可:Boost Software License
 * 来源:https://github.com/AlCash07/ACTL/blob/master/include/actl/geometry/algorithm/intersect/line_convex_polygon.hpp
 * 描述:直线与凸多边形的交线。多边形必须逆时针且无共线点。
 * lineHull(line, poly) 返回描述直线与多边形交线的一对值:
 *  \begin{itemize*}
 *    \item $(-1, -1)$ 若不相交,
 *    \item $(i, -1)$ 若只碰到顶点 $i$,
 *    \item $(i, i)$ 若与边 $(i, i+1)$ 重合,
 *    \item $(i, j)$ 若穿过边 $(i, i+1)$ 与 $(j, j+1)$。
 *  \end{itemize*}
 *  后一种情况中,若穿过顶点 $i$,视为发生在边 $(i, i+1)$ 上。
 *  返回的点按直线碰到多边形的顺序排列。
 * \texttt{extrVertex} 返回凸包在直线方向投影最大的点。
 * 时间:O(\log n)
 * 状态:已对拍
 */
#pragma once

#include "Point.h"

#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template <class P>
int extrVertex(vector<P> &poly, P dir) {
    int n = (int)poly.size(), lo = 0, hi = n;
    if (extr(0)) return 0;
    while (lo + 1 < hi) {
        int m = (lo + hi) / 2;
        if (extr(m)) return m;
        int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
        (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
    }
    return lo;
}

#define cmpL(i) sgn(a.cross(poly[i], b))
template <class P>
array<int, 2> lineHull(P a, P b, vector<P> &poly) {
    int endA = extrVertex(poly, (a - b).perp());
    int endB = extrVertex(poly, (b - a).perp());
    if (cmpL(endA) < 0 || cmpL(endB) > 0)
        return {-1, -1};
    array<int, 2> res;

    for (int i = 0; i < 2; i++) {
        int lo = endB, hi = endA, n = (int)poly.size();
        while ((lo + 1) % n != hi) {
            int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
            (cmpL(m) == cmpL(endB) ? lo : hi) = m;
        }
        res[i] = (lo + !cmpL(hi)) % n;
        swap(endA, endB);
    }
    if (res[0] == res[1]) return {res[0], -1};
    if (!cmpL(res[0]) && !cmpL(res[1])) {
        switch ((res[0] - res[1] + (int)poly.size() + 1) % (int)poly.size()) {
            case 0: return {res[0], res[0]};
            case 2: return {res[1], res[1]};
        }
    }
    return res;
}
