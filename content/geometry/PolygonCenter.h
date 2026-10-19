/**
 * 作者:Ulf Lundstrom
 * 日期:2009-04-08
 * 许可:CC0
 * 来源:
 * 描述:返回多边形的重心。
 * 时间:O(n)
 * 状态:已测试
 */
#pragma once

#include "Point.h"

using P = Point<double>;
P polygonCenter(const vector<P> &v) {
    P res(0, 0);
    double A = 0;

    for (int i = 0, j = (int)v.size() - 1; i < (int)v.size(); j = i++) {
        res = res + (v[i] + v[j]) * v[j].cross(v[i]);
        A += v[j].cross(v[i]);
    }

    return res / A / 3;
}
