/**
 * 作者:Oleksandr Bacherikov, chilli
 * 日期:2019-05-05
 * 许可:Boost Software License
 * 来源:https://codeforces.com/blog/entry/48868
 * 描述:返回凸包(逆时针,无重点/共线点)上距离最大的两点。
 * 状态:已对拍,并在 kattis:roberthood 上测试
 * 时间:O(n)
 */
#pragma once
#include "Point.h"

using P = Point<ll>;
array<P, 2> hullDiameter(vector<P> S) {
    int n = (int)S.size(), j = n < 2 ? 0 : 1;
    pair<ll, array<P, 2>> res({0, {S[0], S[0]}});

    for (int i = 0; i < j; i++) {
        for (;; j = (j + 1) % n) {
            res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
            if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
                break;
        }
    }

    return res.second;
}
