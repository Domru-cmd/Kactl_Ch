/**
 * 作者:Simon Lindholm
 * 许可:CC0
 * 描述:在一组不相交区间上增删区间。
 * 添加时会与被覆盖的区间合并。
 * 区间为 [左闭, 右开)。
 * 时间:O(\log N)
 * 状态:已对拍
 */
#pragma once

set<pii>::iterator addInterval(set<pii> &is, int L, int R) {
    if (L == R) return is.end();
    auto it = is.lower_bound({L, R}), before = it;

    while (it != is.end() && it->first <= R) {
        R = max(R, it->second);
        before = it = is.erase(it);
    }
    if (it != is.begin() && (--it)->second >= L) {
        L = min(L, it->first);
        R = max(R, it->second);
        is.erase(it);
    }

    return is.insert(before, {L, R});
}

void removeInterval(set<pii> &is, int L, int R) {
    if (L == R) return;
    auto it = addInterval(is, L, R);
    auto r2 = it->second;

    if (it->first == L) is.erase(it);
    else (int &)it->second = L;
    if (R != r2) is.emplace(R, r2);
}
