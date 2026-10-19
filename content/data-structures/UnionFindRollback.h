/**
 * 作者:Lukas Polacek, Simon Lindholm
 * 日期:2019-12-26
 * 许可:CC0
 * 来源:民间流传
 * 描述:支持撤销(回滚)的并查集。
 * 若不需要撤销,可忽略 st、time() 与 rollback()。
 * 用法:int t = uf.time(); ...; uf.rollback(t);
 * 时间:O(\log(N))
 * 状态:作为 DirectedMST.h 的一部分已测试
 */
#pragma once

struct RollbackUF {
    vi e;
    vector<pii> st;

    RollbackUF(int n) : e(n, -1) {}

    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    int time() { return (int)st.size(); }

    void rollback(int t) {
        for (int i = time() - 1; i >= t; i--) {
            e[st[i].first] = st[i].second;
        }
        st.resize(t);
    }

    bool join(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        st.push_back({a, e[a]});
        st.push_back({b, e[b]});
        e[a] += e[b];
        e[b] = a;
        return true;
    }
};
