/**
 * 作者:Johan Sannemo
 * 日期:2015-02-06
 * 许可:CC0
 * 来源:民间流传
 * 描述:计算树上的倍增跳表,支持快速向上跳与 LCA。
 * 假设根节点指向自身。
 * 时间:建表 $O(N \log N)$,查询 $O(\log N)$
 * 状态:在 Petrozavodsk 测试,并通过 LCA.cpp 对拍
 */
#pragma once

vector<vi> treeJump(vi &P) {
    int on = 1, d = 1;
    while (on < (int)P.size()) {
        on *= 2;
        d++;
    }
    vector<vi> jmp(d, P);
    for (int i = 1; i < d; i++) {
        for (int j = 0; j < (int)P.size(); j++) {
            jmp[i][j] = jmp[i - 1][jmp[i - 1][j]];
        }
    }
    return jmp;
}

int jmp(vector<vi> &tbl, int nod, int steps) {
    for (int i = 0; i < (int)tbl.size(); i++) {
        if (steps & (1 << i)) nod = tbl[i][nod];
    }
    return nod;
}

int lca(vector<vi> &tbl, vi &depth, int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    a = jmp(tbl, a, depth[a] - depth[b]);
    if (a == b) return a;
    for (int i = (int)tbl.size(); i--;) {
        int c = tbl[i][a], d = tbl[i][b];
        if (c != d) {
            a = c;
            b = d;
        }
    }
    return tbl[0][a];
}
