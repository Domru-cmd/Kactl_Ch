/**
 * 作者:Mattias de Zalenski
 * 日期:2002-11-04
 * 描述:多面体体积的奇妙公式。面应朝外。
 * 状态:已测试
 */
#pragma once

template <class V, class L>
double signedPolyVolume(const V &p, const L &trilist) {
    double v = 0;

    for (auto i : trilist) v += p[i.a].cross(p[i.b]).dot(p[i.c]);

    return v / 6;
}
