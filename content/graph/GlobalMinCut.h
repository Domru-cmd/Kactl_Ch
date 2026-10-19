/**
 * 作者:Simon Lindholm
 * 日期:2021-01-09
 * 许可:CC0
 * 来源:https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm
 * 描述:求无向图的全局最小割(以邻接矩阵表示)。
 * 时间:O(V^3)
 * 状态:与 GomoryHu 一起对拍
 */
#pragma once

pair<int, vi> globalMinCut(vector<vi> mat) {
    pair<int, vi> best = {INT_MAX, {}};
    int n = (int)mat.size();
    vector<vi> co(n);
    for (int i = 0; i < n; i++) co[i] = {i};

    for (int ph = 1; ph < n; ph++) {
        vi w = mat[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) { // 用优先队列可从 O(V^2) 优化到 O(E log V)
            w[t] = INT_MIN;
            s = t;
            t = max_element(w.begin(), w.end()) - w.begin();
            for (int i = 0; i < n; i++) w[i] += mat[t][i];
        }
        best = min(best, {w[t] - mat[t][t], co[t]});
        co[s].insert(co[s].end(), co[t].begin(), co[t].end());
        for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
        for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
        mat[0][t] = INT_MIN;
    }

    return best;
}
