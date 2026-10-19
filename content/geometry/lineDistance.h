/**
 * 作者:Ulf Lundstrom
 * 日期:2009-03-21
 * 许可:CC0
 * 来源:基础数学
 * 描述:\\
\begin{minipage}{75mm}
返回点 p 到过点 a、b 的直线的带符号距离。
从 a 指向 b 看,左侧为正、右侧为负。a==b 时返回 nan。
P 应为 Point<T> 或 Point3D<T>,其中 T 如 double 或 long long。
中间步骤使用乘积,若用 int 或 long long 请注意溢出。
对 Point3D 结果恒非负;对 Point3D,请对叉积结果调用 .dist。
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * 状态:已测试
 */
#pragma once

#include "Point.h"

template <class P>
double lineDist(P a, P b, P p) {
    return (double)(b - a).cross(p - a) / (b - a).dist();
}
