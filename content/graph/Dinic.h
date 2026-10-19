/**
 * 作者:chilli
 * 日期:2019-04-26
 * 许可:CC0
 * 来源:https://cp-algorithms.com/graph/dinic.html
 * 描述:复杂度为 $O(VE\log U)$ 的网络流算法,其中 $U = \max |\text{cap}|$。
 * 若 $U = 1$,为 $O(\min(E^{1/2}, V^{2/3})E)$;二分图匹配为 $O(\sqrt{V}E)$。
 * 状态:在 SPOJ FASTFLOW 与 SPOJ MATCHING 上测试,且已对拍
 */
#pragma once

struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;

        ll flow() { return max(oc - c, 0LL); } // 若需要流量值
    };

    vi lvl, ptr, q;
    vector<vector<Edge>> adj;

    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}

    void addEdge(int a, int b, ll c, ll rcap = 0) {
        adj[a].push_back({b, (int)adj[b].size(), c, c});
        adj[b].push_back({a, (int)adj[a].size() - 1, rcap, rcap});
    }

    ll dfs(int v, int t, ll f) {
        if (v == t || !f) return f;
        for (int &i = ptr[v]; i < (int)adj[v].size(); i++) {
            Edge &e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1) {
                if (ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p;
                    adj[e.to][e.rev].c += p;
                    return p;
                }
            }
        }
        return 0;
    }

    ll calc(int s, int t) {
        ll flow = 0;
        q[0] = s;

        for (int L = 0; L < 31; L++) {
            do { // 随机数据下用 'int L=30' 可能更快
                lvl = ptr = vi((int)q.size());
                int qi = 0, qe = lvl[s] = 1;
                while (qi < qe && !lvl[t]) {
                    int v = q[qi++];
                    for (Edge e : adj[v]) {
                        if (!lvl[e.to] && e.c >> (30 - L)) {
                            q[qe++] = e.to;
                            lvl[e.to] = lvl[v] + 1;
                        }
                    }
                }
                while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
            } while (lvl[t]);
        }
        return flow;
    }

    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
