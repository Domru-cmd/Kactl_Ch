/**
 * 作者:Ulf Lundstrom
 * 日期:2009-03-21
 * 许可:CC0
 * 来源:tinyKACTL
 * 描述:返回多边形带符号面积的两倍。
 *  顺时针枚举得到负面积。T 用 int 时注意溢出!
 * 状态:已对拍,并在 kattis:polygonarea 上测试
 */
#pragma once

#include "Point.h"

template <class T>
T polygonArea2(vector<Point<T>> &v) {
    T a = v.back().cross(v[0]);

    for (int i = 0; i < (int)v.size() - 1; i++) {
        a += v[i].cross(v[i + 1]);
    }

    return a;
}
