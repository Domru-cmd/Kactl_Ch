/**
 * 作者:Ulf Lundstrom
 * 日期:2009-03-21
 * 许可:CC0
 * 来源:
 * 描述:返回从 $s$ 指向 $e$ 看时 $p$ 的位置。1/0/-1 分别对应
 * 左侧/在线上/右侧。
 * 若给出可选参数 $eps$,则当 $p$ 距直线不超过 $eps$ 时返回 0。
 * P 应为 Point<T>,其中 T 如 double 或 long long。
 * 中间步骤使用乘积,若用 int 或 long long 请注意溢出。
 * 用法:
 * 	bool left = sideOf(p1,p2,q)==1;
 * 状态:已测试
 */
#pragma once

#include "Point.h"

template <class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template <class P>
int sideOf(P s, P e, P p, double eps) {
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist() * eps;
    return (a > l) - (a < -l);
}
