/**
 * 作者:Per Austrin, Ulf Lundstrom
 * 日期:2009-04-09
 * 许可:CC0
 * 来源:
 * 描述:\\
\begin{minipage}{75mm}
 对点 r 应用把直线 p0-p1 映到直线 q0-q1 的线性变换(平移、旋转与缩放)。
\end{minipage}
\begin{minipage}{15mm}
\vspace{-8mm}
\includegraphics[width=\textwidth]{content/geometry/linearTransformation}
\vspace{-2mm}
\end{minipage}
 * 状态:未测试
 */
#pragma once

#include "Point.h"

using P = Point<double>;
P linearTransformation(P p0, P p1, P q0, P q1, P r) {
    P dp = p1 - p0, dq = q1 - q0, num(dp.cross(dq), dp.dot(dq));
    return q0 + P((r - p0).cross(num), (r - p0).dot(num)) / dp.dist2();
}
