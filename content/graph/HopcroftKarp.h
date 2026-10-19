/**
 * 作者:Adam Soltan
 * 日期:2026-01-13
 * 许可:CC0
 * 描述:快速的二分图匹配算法。图 $g$ 应为左侧部分的邻居表,
 * $r$ 应为大小与右侧部分相同、初值全为 $-1$ 的 vector。
 * 返回匹配的大小。$r[i]$ 为右侧顶点 $i$ 的匹配对象,
 * 未匹配时为 $-1$。
 * 时间:O(E \sqrt{V})
 * 状态:由 MinimumVertexCover 对拍,并在 Library Checker 上测试
 */
#pragma once

int hopcroftKarp(vector<vi> &g, vi &r) {
    int n = (int)g.size(), res = 0;
    vi l(n, -1), q(n), d(n);

    auto dfs = [&](auto f, int u) -> bool {
        int t = exchange(d[u], 0) + 1;
        for (int v : g[u]) {
            if (r[v] == -1 || (d[r[v]] == t && f(f, r[v])))
                return l[u] = v, r[v] = u, 1;
        }
        return 0;
    };

    for (int t = 0, f = 0;; t = f = 0, d.assign(n, 0)) {
        for (int i = 0; i < n; i++) {
            if (l[i] == -1) {
                q[t++] = i;
                d[i] = 1;
            }
        }
        for (int i = 0; i < t; i++) {
            for (int v : g[q[i]]) {
                if (r[v] == -1) f = 1;
                else if (!d[r[v]]) {
                    d[r[v]] = d[q[i]] + 1;
                    q[t++] = r[v];
                }
            }
        }
        if (!f) return res;
        for (int i = 0; i < n; i++) {
            if (l[i] == -1) res += dfs(dfs, i);
        }
    }
}
