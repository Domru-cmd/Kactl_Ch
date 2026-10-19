/**
 * 作者:Victor Lecomte, chilli
 * 日期:2019-04-27
 * 许可:CC0
 * 来源:https://vlecomte.github.io/cp-geo.pdf
 * 描述:\\
\begin{minipage}{75mm}
若线段 s1-e1 与 s2-e2 有唯一交点,则将其返回。
若无交点,返回空 vector。
若有无穷多交点,返回含 2 个元素的 vector,即公共线段的两个端点。
若 P 为 Point<ll> 且交点坐标不是整数,返回的位置是错误的。
中间步骤使用三个坐标的乘积,若用 int 或 long long 请注意溢出。
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * 用法:
 * vector<P> inter = segInter(s1,e1,s2,e2);
 * if (sz(inter)==1)
 *   cout << "segments intersect at " << inter[0] << endl;
 * 状态:已对拍,并在 kattis:intersection 上测试
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

template <class P>
vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    // 检查交点是否为单个非端点
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {s.begin(), s.end()};
}
