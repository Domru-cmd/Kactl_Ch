/**
 * 作者:Simon Lindholm
 * 日期:2015-02-23
 * 许可:CC0
 * 来源:http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * 描述:计算可能含负权边的图中从 $s$ 出发的最短路。
 * 不可达点的距离为 inf;能通过负权环到达的点的距离为 -inf。
 * 假设 $V^2 \max |w_i| < \tilde{} 2^{63}$。
 * 时间:O(VE)
 * 状态:在 kattis:shortestpath3 上测试
 */
#pragma once

const ll inf = LLONG_MAX;
struct Ed {
    int a, b, w;
    int s() { return a < b ? a : -a; }
};
struct Node { ll dist = inf; int prev = -1; };

void bellmanFord(vector<Node> &nodes, vector<Ed> &eds, int s) {
    nodes[s].dist = 0;
    sort(eds.begin(), eds.end(), [](Ed a, Ed b) { return a.s() < b.s(); });

    int lim = (int)nodes.size() / 2 + 2; // 顶点打乱后为 /3+100
    for (int i = 0; i < lim; i++) {
        for (Ed ed : eds) {
            Node cur = nodes[ed.a], &dest = nodes[ed.b];
            if (abs(cur.dist) == inf) continue;
            ll d = cur.dist + ed.w;
            if (d < dest.dist) {
                dest.prev = ed.a;
                dest.dist = (i < lim - 1 ? d : -inf);
            }
        }
    }
    for (int i = 0; i < lim; i++) {
        for (Ed e : eds) {
            if (nodes[e.a].dist == -inf)
                nodes[e.b].dist = -inf;
        }
    }
}
