/**
 * 作者:Johan Sannemo
 * 许可:CC0
 * 描述:计算覆盖给定区间的最小若干区间的下标。
 * 区间应为 [左闭, 右开)。要支持 [左闭, 右闭],
 * 把 (A) 处改为加上 \texttt{|| R.empty()}。失败(或 G 为空)时返回空集。
 * 时间:O(N \log N)
 * 状态:在 kattis:intervalcover 上测试
 */
#pragma once

template <class T>
vi cover(pair<T, T> G, vector<pair<T, T>> I) {
    vi S((int)I.size()), R;
    iota(S.begin(), S.end(), 0);
    sort(S.begin(), S.end(), [&](int a, int b) { return I[a] < I[b]; });
    T cur = G.first;
    int at = 0;

    while (cur < G.second) { // (A)
        pair<T, int> mx = make_pair(cur, -1);

        while (at < (int)I.size() && I[S[at]].first <= cur) {
            mx = max(mx, make_pair(I[S[at]].second, S[at]));
            at++;
        }
        if (mx.second == -1) return {};
        cur = mx.first;
        R.push_back(mx.second);
    }

    return R;
}
