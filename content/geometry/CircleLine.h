/**
 * 作者:Victor Lecomte, chilli
 * 日期:2019-10-29
 * 许可:CC0
 * 来源:https://vlecomte.github.io/cp-geo.pdf
 * 描述:求圆与直线的交点。
 * 返回含 0、1 或 2 个交点的 vector。
 * P 应为 Point<double>。
 * 状态:已单元测试
 */
#pragma once

#include "Point.h"

template <class P>
vector<P> circleLine(P c, double r, P a, P b) {
    P ab = b - a, p = a + ab * (c - a).dot(ab) / ab.dist2();
    double s = a.cross(b, c), h2 = r * r - s * s / ab.dist2();
    if (h2 < 0) return {};
    if (h2 == 0) return {p};
    P h = ab.unit() * sqrt(h2);
    return {p - h, p + h};
}
