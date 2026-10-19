/**
 * 作者:Simon Lindholm
 * 日期:2017-04-17
 * 许可:CC0
 * 来源:民间流传
 * 描述:求无向图的所有点双连通分量,并对
 *  每个分量中的边运行一次回调。在一个点双连通分量中,
 *  任意两节点之间至少有两条内部不相交的路径
 *  (即存在经过它们的环)。注意一个节点可以出现在多个分量中。
 *  不属于任何分量的边是桥,即不在任何环上。
 * 用法:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...});
 * 时间:O(E + V)
 * 状态:2017 年 MIPT ICPC Workshop 期间测试
 */
#pragma once

vi num, st;
vector<vector<pii>> ed;
int Time;

template <class F>
int dfs(int at, int par, F &f) {
    int me = num[at] = ++Time, top = me;
    for (auto [y, e] : ed[at]) {
        if (e != par) {
            if (num[y]) {
                top = min(top, num[y]);
                if (num[y] < me)
                    st.push_back(e);
            } else {
                int si = (int)st.size();
                int up = dfs(y, e, f);
                top = min(top, up);
                if (up == me) {
                    st.push_back(e);
                    f(vi(st.begin() + si, st.end()));
                    st.resize(si);
                }
                else if (up < me) st.push_back(e);
                else { /* e 是桥 */ }
            }
        }
    }
    return top;
}

template <class F>
void bicomps(F f) {
    num.assign((int)ed.size(), 0);
    for (int i = 0; i < (int)ed.size(); i++) {
        if (!num[i]) dfs(i, -1, f);
    }
}
