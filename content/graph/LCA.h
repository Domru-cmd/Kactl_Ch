/**
 * 作者:chilli, pajenegod
 * 日期:2020-02-20
 * 许可:CC0
 * 来源:民间流传
 * 描述:计算树上最近公共祖先的数据结构
 * (以 0 为根)。C 为树的邻接表,可以有向或无向。
 * 时间:$O(N \log N + Q)$
 * 状态:已对拍
 */
#pragma once

#include "../data-structures/RMQ.h"

struct LCA {
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;

    LCA(vector<vi> &C) : time((int)C.size()), rmq((dfs(C, 0, -1), ret)) {}

    void dfs(vector<vi> &C, int v, int par) {
        time[v] = T++;
        for (int y : C[v]) {
            if (y != par) {
                path.push_back(v);
                ret.push_back(time[v]);
                dfs(C, y, v);
            }
        }
    }

    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    //dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};
