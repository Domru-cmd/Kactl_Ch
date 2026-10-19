/**
 * 作者:chilli, Takanori MAEHARA
 * 日期:2019-11-02
 * 许可:CC0
 * 来源:https://github.com/spaghetti-source/algorithm/blob/master/geometry/rectilinear_mst.cc
 * 描述:给定 N 个点,返回至多 4*N 条边,保证包含以
 * w(p, q) = |p.x - q.x| + |p.y - q.y| 为边权的图的最小生成树。
 * 边形式为 (距离, 起点, 终点)。对结果跑标准 MST 算法即得最终 MST。
 * 时间:O(N \log N)
 * 状态:已对拍
 */
#pragma once
#include "Point.h"

using P = Point<int>;
vector<array<int, 3>> manhattanMST(vector<P> ps) {
    vi id((int)ps.size());
    iota(id.begin(), id.end(), 0);
    vector<array<int, 3>> edges;

    for (int k = 0; k < 4; k++) {
        sort(id.begin(), id.end(), [&](int i, int j) {
            return (ps[i] - ps[j]).x < (ps[j] - ps[i]).y;
        });
        map<int, int> sweep;

        for (int i : id) {
            for (auto it = sweep.lower_bound(-ps[i].y);
                    it != sweep.end(); sweep.erase(it++)) {
                int j = it->second;
                P d = ps[i] - ps[j];
                if (d.y > d.x) break;
                edges.push_back({d.y + d.x, i, j});
            }
            sweep[-ps[i].y] = i;
        }
        for (P &p : ps) {
            if (k & 1) p.x = -p.x;
            else swap(p.x, p.y);
        }
    }

    return edges;
}
