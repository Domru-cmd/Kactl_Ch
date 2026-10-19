/**
 * 作者:Victor Lecomte, chilli
 * 日期:2019-10-29
 * 许可:CC0
 * 来源:https://vlecomte.github.io/cp-geo.pdf
 * 描述:把点 p 投影到直线 ab 上。设 refl=true 则求
 * 点 p 关于直线 ab 的对称点。若 P 为整点且所求点坐标
 * 不是整数,返回的点是错误的。
 * 中间步骤使用三个坐标的乘积,请注意溢出。
 * 状态:已对拍
 */
#pragma once

#include "Point.h"

template <class P>
P lineProj(P a, P b, P p, bool refl = false) {
    P v = b - a;
    return p - v.perp() * (1 + refl) * v.cross(p - a) / v.dist2();
}
