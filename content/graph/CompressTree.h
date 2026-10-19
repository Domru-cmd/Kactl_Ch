/**
 * 作者:Simon Lindholm
 * 日期:2016-01-14
 * 许可:CC0
 * 描述:给定一棵有根树与节点子集 S,通过加入至多 $|S|-1$ 个
 * 两两 LCA 并压缩边,求出包含全部节点的最小子树。
 * 返回 (par, orig\_index) 的列表,表示一棵以 0 为根的树。
 * 根指向自身。
 * 时间:$O(|S| \log |S|)$
 * 状态:在 CodeForces 上测试
 */
#pragma once

#include "LCA.h"

using vpi = vector<pair<int, int>>;
vpi compressTree(LCA &lca, const vi &subset) {
    static vi rev;
    rev.resize((int)lca.time.size());
    vi li = subset, &T = lca.time;
    auto cmp = [&](int a, int b) { return T[a] < T[b]; };
    sort(li.begin(), li.end(), cmp);
    int m = (int)li.size() - 1;

    for (int i = 0; i < m; i++) {
        int a = li[i], b = li[i + 1];
        li.push_back(lca.lca(a, b));
    }
    sort(li.begin(), li.end(), cmp);
    li.erase(unique(li.begin(), li.end()), li.end());
    for (int i = 0; i < (int)li.size(); i++) rev[li[i]] = i;
    vpi ret = {pii(0, li[0])};

    for (int i = 0; i < (int)li.size() - 1; i++) {
        int a = li[i], b = li[i + 1];
        ret.emplace_back(rev[lca.lca(a, b)], b);
    }

    return ret;
}
