/**
 * 作者:Stjepan Glavina, chilli
 * 日期:2019-05-05
 * 许可:Unlicense
 * 来源:https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * 描述:
\\\begin{minipage}{75mm}
按逆时针顺序返回凸包上的点。
处于凸包上另外两点之间的边上的点不计入凸包。
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * 时间:O(n \log n)
 * 状态:已对拍,并在 kattis:convexhull 上测试
*/
#pragma once

#include "Point.h"

using P = Point<ll>;
vector<P> convexHull(vector<P> pts) {
    if ((int)pts.size() <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<P> h((int)pts.size() + 1);
    int s = 0, t = 0;

    for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end())) {
        for (P p : pts) {
            while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
            h[t++] = p;
        }
    }

    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
