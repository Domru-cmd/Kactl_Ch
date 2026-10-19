/**
 * 作者:Jeremy Lim, Joshua Andersson
 * 日期:2026-07-09
 * 许可:CC0
 * 来源:https://github.com/scipy/scipy/blob/main/scipy/optimize/rectangular_lsap/rectangular_lsap.cpp
 * 描述:给定带权二分图,把左侧每个节点与右侧某节点匹配,
 * 使没有节点出现在两个匹配中且边权之和最小。输入
 * cost[N][M],其中 cost[i][j] = L[i] 与 R[j] 匹配的代价,
 * 返回 (最小代价, match),其中 L[i] 与
 * R[match[i]] 匹配。代价取反可用于求最大权。要求 $N \le M$。
 * 时间:O(N^2M)
 * 状态:在 kattis:cordonbleu、kattis:engaging 上测试,已对拍
 */
#pragma once

template <class T>
pair<T, vi> weightedMatching(vector<vector<T>> &C) {
    int i = (int)C.size(), m = i ? (int)C[0].size() : 0, c, s, r;
    vector<T> dist(m), pot(m);
    vi match(i), rev(m, -1), cols(m), prev(m);
    T d = 0, nd, cost = 0;

    while (i--) {
        for (int c = 0; c < m; c++) {
            dist[c] = C[i][c];
            cols[c] = c;
            prev[c] = i;
        }
        for (s = 0;;) {
            for (int j = s; j < m; j++) {
                c = cols[j];
                nd = dist[c] - pot[c];
                if (j == s || d > nd) {
                    d = nd;
                    swap(cols[s], cols[j]);
                }
            }
            if ((r = rev[c = cols[s++]]) == -1) break;
            for (int j = 0; j < m; j++) {
                if (dist[j] > (nd = C[r][j] - C[r][c] + dist[c])) {
                    dist[j] = nd;
                    prev[j] = r;
                }
            }
        }
        cost += dist[c];
        while (s--) pot[cols[s]] = dist[cols[s]] - d;
        for (; r != i; swap(c, match[r]))
            r = rev[c] = prev[c];
    }

    return {cost, match};
}
