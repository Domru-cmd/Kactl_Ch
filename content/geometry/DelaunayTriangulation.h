/**
 * 作者:Mattias de Zalenski
 * 日期:未知
 * 来源:Geometry in C
 * 描述:计算点集的 Delaunay 三角剖分。
 *  每个外接圆内不含任何输入点。
 *  若任意三点共线或任意四点共圆,行为未定义。
 * 时间:O(n^2)
 * 状态:已对拍
 */
#pragma once

#include "Point.h"
#include "3dHull.h"

template <class P, class F>
void delaunay(vector<P> &ps, F trifun) {
    if ((int)ps.size() == 3) {
        int d = (ps[0].cross(ps[1], ps[2]) < 0);
        trifun(0, 1 + d, 2 - d);
    }
    vector<P3> p3;

    for (P p : ps) p3.emplace_back(p.x, p.y, p.dist2());
    if ((int)ps.size() > 3) {
        for (auto t : hull3d(p3)) {
            if ((p3[t.b] - p3[t.a]).cross(
                    p3[t.c] - p3[t.a]).dot(P3(0, 0, 1)) < 0)
                trifun(t.a, t.c, t.b);
        }
    }
}
