/**
 * 作者:chilli, Takanori MAEHARA
 * 日期:2020-04-03
 * 许可:CC0
 * 来源:https://github.com/spaghetti-source/algorithm/blob/master/graph/gomory_hu_tree.cc#L102
 * 描述:给定表示无向流网络的边表,
 * 返回 Gomory-Hu 树的边。任意两点间的最大流
 * 等于 Gomory-Hu 树路径上的最小边权。
 * 时间:$O(V)$ 次流计算
 * 状态:在 CERC 2015 J 上测试,已对拍
 *
 * 细节:这里用的并非原始 Gomory-Hu,而是 Gusfield 的
 * 简化版本:"Very simple methods for all
 * pairs network flow analysis"。这里使用 PushRelabel,
 * 但任何支持 `leftOfMinCut` 的流实现都可以。
 */
#pragma once

#include "PushRelabel.h"

using Edge = array<ll, 3>;
vector<Edge> gomoryHu(int N, vector<Edge> ed) {
    vector<Edge> tree;
    vi par(N);

    for (int i = 1; i < N; i++) {
        PushRelabel D(N); // Dinic 也可以
        for (Edge t : ed) D.addEdge(t[0], t[1], t[2], t[2]);
        tree.push_back({i, par[i], D.calc(i, par[i])});
        for (int j = i + 1; j < N; j++) {
            if (par[j] == par[i] && D.leftOfMinCut(j)) par[j] = i;
        }
    }

    return tree;
}
