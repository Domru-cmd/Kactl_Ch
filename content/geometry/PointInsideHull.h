/**
 * 作者:chilli
 * 日期:2019-05-17
 * 许可:CC0
 * 来源:https://github.com/ngthanhtrung23/ACM_Notebook_new
 * 描述:判断点 t 是否在凸包内(逆时针
 * 顺序,无共线点)。返回点是否在
 * 凸包内。若 strict 为真,边界上的点不计入。
 * 用法:
 * 状态:已对拍
 * 时间:O(\log N)
 */
#pragma once

#include "Point.h"
#include "sideOf.h"
#include "OnSegment.h"

using P = Point<ll>;

bool inHull(const vector<P> &l, P p, bool strict = true) {
    int a = 1, b = (int)l.size() - 1, r = !strict;
    if ((int)l.size() < 3) return r && onSegment(l[0], l.back(), p);
    if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
    if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p) <= -r)
        return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
    }
    return sgn(l[a].cross(l[b], p)) < r;
}
