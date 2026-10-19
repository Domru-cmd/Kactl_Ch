/**
 * 作者:Mårten Wiman
 * 许可:CC0
 * 来源:Pisinger 1999, "Linear Time Algorithms for Knapsack Problems with Bounded Weights"
 * 描述:给定 N 个非负整数权值 w 与非负目标 t,
 * 计算可作为某些权值子集和的最大的 S <= t。
 * 时间:O(N \max(w_i))
 * 状态:在 kattis:eavesdropperevasion 上测试,已对拍
 */
#pragma once

int knapsack(vi w, int t) {
    int a = 0, b = 0, x;

    while (b < (int)w.size() && a + w[b] <= t) a += w[b++];
    if (b == (int)w.size()) return a;
    int m = *max_element(w.begin(), w.end());
    vi u, v(2 * m, -1);
    v[a + m - t] = b;

    for (int i = b; i < (int)w.size(); i++) {
        u = v;

        for (x = 0; x < m; x++) v[x + w[i]] = max(v[x + w[i]], u[x]);
        for (x = 2 * m; --x > m;) {
            for (int j = max(0, u[x]); j < v[x]; j++) {
                v[x - w[j]] = max(v[x - w[j]], j);
            }
        }
    }
    for (a = t; v[a + m - t] < 0; a--);
    return a;
}
