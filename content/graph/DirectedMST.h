/**
 * 作者:chilli, Takanori MAEHARA, Benq, Simon Lindholm
 * 日期:2019-05-10
 * 许可:CC0
 * 来源:https://github.com/spaghetti-source/algorithm/blob/master/graph/arborescence.cc
 * 以及 https://github.com/bqi343/USACO/blob/42d177dfb9d6ce350389583cfa71484eb8ae614c/Implementations/content/graphs%20(12)/Advanced/DirectedMST.h 的重建部分
 * 描述:求有向图以给定节点为根的最小生成树
 * (树形图)。若不存在 MST,返回 -1。
 * 时间:O(E \log V)
 * 状态:已对拍,并在 NWERC 2018 fastestspeedrun 上测试
 */
#pragma once

#include "../data-structures/UnionFindRollback.h"

struct Edge { int a, b; ll w; };
struct Node { /// 惰性斜堆节点
    Edge key;
    Node *l, *r;
    ll delta;

    void prop() {
        key.w += delta;
        if (l) l->delta += delta;
        if (r) r->delta += delta;
        delta = 0;
    }
    Edge top() {
        prop();
        return key;
    }
};
Node *merge(Node *a, Node *b) {
    if (!a || !b) return a ? a : b;
    a->prop();
    b->prop();
    if (a->key.w > b->key.w) swap(a, b);
    swap(a->l, (a->r = merge(b, a->r)));
    return a;
}
void pop(Node *&a) {
    a->prop();
    a = merge(a->l, a->r);
}

pair<ll, vi> dmst(int n, int r, vector<Edge> &g) {
    RollbackUF uf(n);
    vector<Node *> heap(n);

    for (Edge e : g) heap[e.b] = merge(heap[e.b], new Node{e});
    ll res = 0;
    vi seen(n, -1), path(n), par(n);
    seen[r] = r;
    vector<Edge> Q(n), in(n, {-1, -1}), comp;
    deque<tuple<int, int, vector<Edge>>> cycs;

    for (int s = 0; s < n; s++) {
        int u = s, qi = 0, w;
        while (seen[u] < 0) {
            if (!heap[u]) return {-1, {}};
            Edge e = heap[u]->top();
            heap[u]->delta -= e.w;
            pop(heap[u]);
            Q[qi] = e;
            path[qi++] = u;
            seen[u] = s;
            res += e.w;
            u = uf.find(e.a);
            if (seen[u] == s) { /// 找到环,缩点
                Node *cyc = 0;
                int end = qi, time = uf.time();
                do cyc = merge(cyc, heap[w = path[--qi]]);
                while (uf.join(u, w));
                u = uf.find(u);
                heap[u] = cyc;
                seen[u] = -1;
                cycs.push_front({u, time, {&Q[qi], &Q[end]}});
            }
        }
        for (int i = 0; i < qi; i++) in[uf.find(Q[i].b)] = Q[i];
    }

    for (auto &[u, t, comp] : cycs) { // 还原解(可选)
        uf.rollback(t);
        Edge inEdge = in[u];
        for (auto &e : comp) in[uf.find(e.b)] = e;
        in[uf.find(inEdge.b)] = inEdge;
    }
    for (int i = 0; i < n; i++) par[i] = in[i].a;
    return {res, par};
}
