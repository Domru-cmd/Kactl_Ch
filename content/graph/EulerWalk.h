/**
 * 作者:Simon Lindholm
 * 日期:2019-12-31
 * 许可:CC0
 * 来源:民间流传
 * 描述:无向/有向图的欧拉路/回路算法。
 * 输入应为 (终点, 全局边编号) 的 vector,其中
 * 无向图的正反两条边共用同一编号。
 * 返回欧拉路/回路的节点列表,起点与终点均为 src;
 * 若不存在回路/路,返回空列表。
 * 要取回边编号,给 s 和 ret 加上 .second。
 * 时间:O(V + E)
 * 状态:已对拍
 */
#pragma once

vi eulerWalk(vector<vector<pii>> &gr, int nedges, int src = 0) {
    int n = (int)gr.size();
    vi D(n), its(n), eu(nedges), ret, s = {src};
    D[src]++; // 以允许欧拉路(而不只是回路)

    while (!s.empty()) {
        int x = s.back(), y, e, &it = its[x], end = (int)gr[x].size();
        if (it == end) {
            ret.push_back(x);
            s.pop_back();
            continue;
        }
        tie(y, e) = gr[x][it++];
        if (!eu[e]) {
            D[x]--;
            D[y]++;
            eu[e] = 1;
            s.push_back(y);
        }
    }
    for (int x : D) {
        if (x < 0 || (int)ret.size() != nedges + 1) return {};
    }
    return {ret.rbegin(), ret.rend()};
}
