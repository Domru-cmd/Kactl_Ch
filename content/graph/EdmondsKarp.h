/**
 * 作者:Chen Xing
 * 日期:2009-10-13
 * 许可:CC0
 * 来源:无
 * 描述:复杂度保证为 $O(VE^2)$ 的网络流算法。要得到每条边的流量,
 * 比较前后容量,只取正值即可。
 * 状态:已对拍
 */
#pragma once

template <class T>
T edmondsKarp(vector<unordered_map<int, T>> &graph, int source, int sink) {
    assert(source != sink);
    T flow = 0;
    vi par((int)graph.size()), q = par;

    for (;;) {
        fill(par.begin(), par.end(), -1);
        par[source] = 0;
        int ptr = 1;
        q[0] = source;

        for (int i = 0; i < ptr; i++) {
            int x = q[i];
            for (auto e : graph[x]) {
                if (par[e.first] == -1 && e.second > 0) {
                    par[e.first] = x;
                    q[ptr++] = e.first;
                    if (e.first == sink) goto out;
                }
            }
        }
        return flow;
out:
        T inc = numeric_limits<T>::max();
        for (int y = sink; y != source; y = par[y])
            inc = min(inc, graph[par[y]][y]);

        flow += inc;
        for (int y = sink; y != source; y = par[y]) {
            int p = par[y];
            if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
            graph[y][p] += inc;
        }
    }
}
