/**
 * 作者:Victor Lecomte, chilli
 * 日期:2019-05-05
 * 许可:CC0
 * 来源:https://vlecomte.github.io/cp-geo.pdf
 * 描述:\\
\begin{minipage}{75mm}
若过 s1,e1 与 s2,e2 的直线有唯一交点,返回 \{1, 交点\}。
若无交点返回 \{0, (0,0)\};若有无穷多交点返回 \{-1, (0,0)\}。
若 P 为 Point<ll> 且交点坐标不是整数,返回的位置是错误的。
中间步骤使用三个坐标的乘积,若用 int 或 ll 请注意溢出。
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * 用法:
 * 	auto res = lineInter(s1,e1,s2,e2);
 * 	if (res.first == 1)
 * 		cout << "intersection point at " << res.second << endl;
 * 状态:已对拍,并通过半平面测试验证
 */
#pragma once

#include "Point.h"

template <class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // 若平行
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}
