/**
 * 作者:Simon Lindholm
 * 日期:2019-12-28
 * 许可:CC0
 * 来源:https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * 描述:把询问看作点,求一条近似 TSP 路线的顺序来处理区间(或树上路径)询问,
 * 相邻询问之间通过在端点处增删元素来转移。
 * 若值在树边上,把 \texttt{step} 改为增删边 $(a, c)$,并去掉开头的 \texttt{add} 调用(保留 \texttt{in})。
 * 时间:O(N \sqrt Q)
 * 状态:已对拍
 */
#pragma once

void add(int ind, int end) { ... } // 加入 a[ind](end 为 0 或 1)
void del(int ind, int end) { ... } // 删除 a[ind]
int calc() { ... } // 计算当前答案

vi mo(vector<pii> Q) {
    int L = 0, R = 0, blk = 350; // ~N/sqrt(Q)
    vi s((int)Q.size()), res = s;

#define K(x) pii(x.first/blk, x.second ^ -(x.first/blk & 1))
    iota(s.begin(), s.end(), 0);
    sort(s.begin(), s.end(), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });

    for (int qi : s) {
        pii q = Q[qi];

        while (L > q.first) add(--L, 0);
        while (R < q.second) add(R++, 1);
        while (L < q.first) del(L++, 0);
        while (R > q.second) del(--R, 1);
        res[qi] = calc();
    }

    return res;
}

vi moTree(vector<array<int, 2>> Q, vector<vi> &ed, int root = 0) {
    int N = (int)ed.size(), pos[2] = {}, blk = 350; // ~N/sqrt(Q)
    vi s((int)Q.size()), res = s, I(N), L(N), R(N), in(N), par(N);

    add(0, 0);
    in[0] = 1;
    auto dfs = [&](int x, int p, int dep, auto &f) -> void {
        par[x] = p;
        L[x] = N;
        if (dep) I[x] = N++;
        for (int y : ed[x]) if (y != p) f(y, x, !dep, f);
        if (!dep) I[x] = N++;
        R[x] = N;
    };
    dfs(root, -1, 0, dfs);

#define K(x) pii(I[x[0]] / blk, I[x[1]] ^ -(I[x[0]] / blk & 1))
    iota(s.begin(), s.end(), 0);
    sort(s.begin(), s.end(), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });

    for (int qi : s) {
        for (int end = 0; end < 2; end++) {
            int &a = pos[end], b = Q[qi][end], i = 0;
#define step(c) { if (in[c]) { del(a, end); in[a] = 0; } \
                  else { add(c, end); in[c] = 1; } a = c; }
            while (!(L[b] <= L[a] && R[a] <= R[b])) {
                I[i++] = b;
                b = par[b];
            }
            while (a != b) step(par[a]);
            while (i--) step(I[i]);
            if (end) res[qi] = calc();
        }
    }

    return res;
}
