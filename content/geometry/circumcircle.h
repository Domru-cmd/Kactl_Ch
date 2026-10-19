/**
 * 作者:Ulf Lundstrom
 * 日期:2009-04-11
 * 许可:CC0
 * 来源:http://en.wikipedia.org/wiki/Circumcircle
 * 描述:\\
\begin{minipage}{75mm}
三角形的外接圆是过其三个顶点的圆。ccRadius 返回过点 A、B、C 的圆的半径,
ccCenter 返回同一个圆的圆心。
\end{minipage}
\begin{minipage}{15mm}
\vspace{-2mm}
\includegraphics[width=\textwidth]{content/geometry/circumcircle}
\end{minipage}
 * 状态:已测试
 */
#pragma once

#include "Point.h"

using P = Point<double>;
double ccRadius(P A, P B, P C) {
    return (B - A).dist() * (C - B).dist() * (A - C).dist() /
            abs((B - A).cross(C - A)) / 2;
}

P ccCenter(P A, P B, P C) {
    P b = C - A, c = B - A;
    return A + (b * c.dist2() - c * b.dist2()).perp() / b.cross(c) / 2;
}
