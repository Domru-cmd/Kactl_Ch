/**
 * 作者:Lukas Polacek
 * 日期:2009-10-28
 * 许可:CC0
 * 来源:捷克图论教材(作者 Demel)。(Tarjan 算法)
 * 描述:求有向图的强连通分量。
 * 若顶点 $u, v$ 属于同一分量,则从 $v$ 可达 $u$,反之亦然。
 * 用法:scc(graph, [\&](vi\& v) { ... }) 按逆拓扑序
 * 访问所有分量。comp[i] 保存节点 i 的分量编号
 * (一个分量只会连向编号更小的分量)。ncomps 为分量个数。
 * 时间:O(E + V)
 * 状态:对 N <= 5 已暴力验证
 */
#pragma once

vi val, comp, z, cont;
int Time, ncomps;

template <class G, class F>
int dfs(int j, G &g, F &f) {
    int low = val[j] = ++Time, x;
    z.push_back(j);
    for (auto e : g[j]) {
        if (comp[e] < 0)
            low = min(low, val[e] ? val[e] : dfs(e, g, f));
    }

    if (low == val[j]) {
        do {
            x = z.back();
            z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j);
        f(cont);
        cont.clear();
        ncomps++;
    }
    return val[j] = low;
}

template <class G, class F>
void scc(G &g, F f) {
    int n = (int)g.size();
    val.assign(n, 0);
    comp.assign(n, -1);
    Time = ncomps = 0;
    for (int i = 0; i < n; i++) {
        if (comp[i] < 0) dfs(i, g, f);
    }
}
