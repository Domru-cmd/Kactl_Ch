/**
 * 作者:Simon Lindholm
 * 日期:2019-04-17
 * 许可:CC0
 * 来源:https://codeforces.com/blog/entry/58747
 * 描述:求最近点对。
 * 时间:O(n \log n)
 * 状态:已对拍
 */
#pragma once

#include "Point.h"

using P = Point<ll>;
pair<P, P> closest(vector<P> v) {
    assert((int)v.size() > 1);
    set<P> S;
    sort(v.begin(), v.end(), [](P a, P b) { return a.y < b.y; });
    pair<ll, pair<P, P>> ret{LLONG_MAX, {P(), P()}};
    int j = 0;

    for (P p : v) {
        P d{1 + (ll)sqrt(ret.first), 0};
        while (v[j].y <= p.y - d.x) {
            S.erase(v[j++]);
        }
        auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);

        for (; lo != hi; lo++) {
            ret = min(ret, {(*lo - p).dist2(), {*lo, p}});
        }
        S.insert(p);
    }

    return ret.second;
}
