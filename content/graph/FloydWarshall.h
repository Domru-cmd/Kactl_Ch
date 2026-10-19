/**
 * 作者:Simon Lindholm
 * 日期:2016-12-15
 * 许可:CC0
 * 来源:http://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
 * 描述:计算可能含负权边的有向图的全源最短路。
 * 输入为距离矩阵 $m$,其中 $i$ 与 $j$ 不相邻时 $m[i][j] = \texttt{inf}$。
 * 输出时 $m[i][j]$ 被设为 $i$ 到 $j$ 的最短距离:无路径为 \texttt{inf},
 * 路径经过负权环则为 \texttt{-inf}。
 * 时间:O(N^3)
 * 状态:轻度测试
 */
#pragma once

const ll inf = 1LL << 62;
void floydWarshall(vector<vector<ll>> &m) {
    int n = (int)m.size();
    for (int i = 0; i < n; i++) m[i][i] = min(m[i][i], 0LL);

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (m[i][k] != inf && m[k][j] != inf) {
                    auto newDist = max(m[i][k] + m[k][j], -inf);
                    m[i][j] = min(m[i][j], newDist);
                }
            }
        }
    }
    for (int k = 0; k < n; k++) {
        if (m[k][k] < 0) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
                }
            }
        }
    }
}
