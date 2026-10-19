/**
 * 作者:Benjamin Qi, Oleksandr Kulkov, chilli
 * 日期:2020-01-12
 * 许可:CC0
 * 来源:https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * 描述:把树分解为顶点不相交的重链与轻边,使任意叶子到根
 * 的路径上至多 $\log(n)$ 条轻边。代码做的是区间加与区间最大值
 * 查询,但可以支持路径与子树上可交换的线段树修改/查询。
 * 输入为完整的邻接表。VALS\_EDGES 为真表示
 * 值存在边上而非节点上。所有值初始化为线段树默认值。
 * 根必须为 0。
 * 时间:O((\log N)^2)
 * 状态:对照旧版 HLD 已对拍
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

template <bool VALS_EDGES>
struct HLD {
    int N, tim = 0;
    vector<vi> adj;
    vi par, siz, rt, pos;
    Node *tree;

    HLD(vector<vi> adj_)
        : N((int)adj_.size()), adj(adj_), par(N, -1), siz(N, 1),
          rt(N), pos(N), tree(new Node(0, N)) {
        dfsSz(0);
        dfsHld(0);
    }

    void dfsSz(int v) {
        for (int &u : adj[v]) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
            par[u] = v;
            dfsSz(u);
            siz[v] += siz[u];
            if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
        }
    }

    void dfsHld(int v) {
        pos[v] = tim++;
        for (int u : adj[v]) {
            rt[u] = (u == adj[v][0] ? rt[v] : u);
            dfsHld(u);
        }
    }

    template <class B>
    void process(int u, int v, B op) {
        for (;; v = par[rt[v]]) {
            if (pos[u] > pos[v]) swap(u, v);
            if (rt[u] == rt[v]) break;
            op(pos[rt[v]], pos[v] + 1);
        }
        op(pos[u] + VALS_EDGES, pos[v] + 1);
    }

    void modifyPath(int u, int v, int val) {
        process(u, v, [&](int l, int r) { tree->add(l, r, val); });
    }

    int queryPath(int u, int v) { // 依题目修改
        int res = -1e9;
        process(u, v, [&](int l, int r) {
            res = max(res, tree->query(l, r));
        });
        return res;
    }

    int querySubtree(int v) { // modifySubtree 类似
        return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
    }
};
