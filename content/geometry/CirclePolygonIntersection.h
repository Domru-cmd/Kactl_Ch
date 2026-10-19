/**
 * 作者:chilli, Takanori MAEHARA
 * 日期:2019-10-31
 * 许可:CC0
 * 来源:https://github.com/spaghetti-source/algorithm/blob/master/geometry/_geom.cc#L744
 * 描述:返回圆与逆时针多边形的交的面积。
 * 时间:O(n)
 * 状态:在 GNYR 2019 Gerrymandering 上测试,已对拍
 */
#pragma once

#include "../../content/geometry/Point.h"

using P = Point<double>;
#define arg(p, q) atan2(p.cross(q), p.dot(q))
double circlePoly(P c, double r, vector<P> ps) {
    auto tri = [&](P p, P q) {
        auto r2 = r * r / 2;
        P d = q - p;
        auto a = d.dot(p) / d.dist2(), b = (p.dist2() - r * r) / d.dist2();
        auto det = a * a - b;
        if (det <= 0) return arg(p, q) * r2;
        auto s = max(0., -a - sqrt(det)), t = min(1., -a + sqrt(det));
        if (t < 0 || 1 <= s) return arg(p, q) * r2;
        P u = p + d * s, v = q + d * (t - 1);
        return arg(p, u) * r2 + u.cross(v) / 2 + arg(v, q) * r2;
    };
    auto sum = 0.0;

    for (int i = 0; i < (int)ps.size(); i++) {
        sum += tri(ps[i] - c, ps[(i + 1) % (int)ps.size()] - c);
    }

    return sum;
}
