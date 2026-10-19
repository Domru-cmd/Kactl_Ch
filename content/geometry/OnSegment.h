/**
 * 作者:Victor Lecomte, chilli
 * 日期:2019-04-26
 * 许可:CC0
 * 来源:https://vlecomte.github.io/cp-geo.pdf
 * 描述:返回 p 是否在线段 s-e 上(为真当且仅当)。
 * 使用 Point<double> 时请改用 \texttt{(segDist(s,e,p)<=epsilon)}。
 * 状态:
 */
#pragma once

#include "Point.h"

template <class P>
bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
