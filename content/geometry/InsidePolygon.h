/**
 * 作者:Victor Lecomte, chilli
 * 日期:2019-04-26
 * 许可:CC0
 * 来源:https://vlecomte.github.io/cp-geo.pdf
 * 描述:返回 p 是否在多边形内。若 strict 为真,
 * 边界上的点返回 false。中间步骤使用乘积,请注意溢出。
 * 时间:O(n)
 * 用法:
 * vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 * bool in = inPolygon(v, P{3, 3}, false);
 * 状态:已对拍,并在 kattis:pointinpolygon 上测试
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"
#include "SegmentDistance.h"

template <class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
    int cnt = 0, n = (int)p.size();

    for (int i = 0; i < n; i++) {
        P q = p[(i + 1) % n];
        if (onSegment(p[i], q, a)) return !strict;
        // 或者:if (segDist(p[i], q, a) <= eps) return !strict;
        cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
    }

    return cnt;
}
