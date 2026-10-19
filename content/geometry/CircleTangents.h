/**
 * 作者:Victor Lecomte, chilli
 * 日期:2019-10-31
 * 许可:CC0
 * 来源:https://vlecomte.github.io/cp-geo.pdf
 * 描述:求两圆的外公切线;若 r2 取负则求内公切线。
 * 可返回 0、1 或 2 条切线 —— 若一圆包含另一圆则为 0
 * (内公切线情形下两圆相交或相同也为 0);
 * 若两圆相切则为 1(此时 .first = .second,切线与连心线垂直)。
 * .first 与 .second 分别为圆 1 与圆 2 上的切点。
 * 求圆与点集的切线时,把 r2 设为 0。
 * 状态:已测试
 */
#pragma once

#include "Point.h"

template <class P>
vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
    P d = c2 - c1;
    double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) return {};
    vector<pair<P, P>> out;

    for (double sign : {-1, 1}) {
        P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
        out.push_back({c1 + v * r1, c2 + v * r2});
    }
    if (h2 == 0) out.pop_back();
    return out;
}
