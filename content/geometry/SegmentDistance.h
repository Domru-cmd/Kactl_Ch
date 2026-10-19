/**
 * 作者:Ulf Lundstrom
 * 日期:2009-03-21
 * 许可:CC0
 * 来源:
 * 描述:\\
\begin{minipage}{75mm}
返回点 p 到线段 s-e 的最短距离。
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * 用法:
 * 	Point<double> a, b(2,2), p(1,1);
 * 	bool onSegment = segDist(a,b,p) < 1e-10;
 * 状态:已测试
 */
#pragma once

#include "Point.h"

using P = Point<double>;
double segDist(P s, P e, P p) {
    if (s == e) return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}
