/**
 * 作者:Ulf Lundstrom
 * 日期:2009-03-21
 * 许可:CC0
 * 来源:
 * 描述:\\
\begin{minipage}{75mm}
 返回一个多边形的顶点,其中已切掉从 s 指向 e 的直线左侧的部分。
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/PolygonCut}
\vspace{-6mm}
\end{minipage}
 * 用法:
 * 	vector<P> p = ...;
 * 	p = polygonCut(p, P(0,0), P(1,0));
 * 状态:已测试,但不够充分
 */
#pragma once

#include "Point.h"

using P = Point<double>;
vector<P> polygonCut(const vector<P> &poly, P s, P e) {
    vector<P> res;

    for (int i = 0; i < (int)poly.size(); i++) {
        P cur = poly[i], prev = i ? poly[i - 1] : poly.back();
        auto a = s.cross(e, cur), b = s.cross(e, prev);
        if ((a < 0) != (b < 0))
            res.push_back(cur + (prev - cur) * (a / (a - b)));
        if (a < 0)
            res.push_back(cur);
    }

    return res;
}
