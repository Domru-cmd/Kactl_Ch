/**
 * 作者:Simon Lindholm
 * 日期:2016-08-27
 * 许可:CC0
 * 来源:自己整理
 * 描述:在 $\mathbb F_2$ 上解 $Ax = b$。若有多解,返回任意一个。
 *  返回秩;无解返回 -1。会破坏 $A$ 与 $b$。
 * 时间:O(n^2 m)
 * 状态:对 n, m <= 4 已暴力验证
 */
#pragma once

using bs = bitset<1000>;

int solveLinear(vector<bs> &A, vi &b, bs &x, int m) {
    int n = (int)A.size(), rank = 0, br;
    assert(m <= (int)x.size());
    vi col(m);
    iota(col.begin(), col.end(), 0);

    for (int i = 0; i < n; i++) {
        for (br = i; br < n; br++) {
            if (A[br].any()) break;
        }
        if (br == n) {
            for (int j = i; j < n; j++) {
                if (b[j]) return -1;
            }
            break;
        }
        int bc = (int)A[br]._Find_next(i - 1);
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        for (int j = 0; j < n; j++) {
            if (A[j][i] != A[j][bc]) {
                A[j].flip(i);
                A[j].flip(bc);
            }
        }
        for (int j = i + 1; j < n; j++) {
            if (A[j][i]) {
                b[j] ^= b[i];
                A[j] ^= A[i];
            }
        }
        rank++;
    }

    x = bs();
    for (int i = rank; i--;) {
        if (!b[i]) continue;
        x[col[i]] = 1;
        for (int j = 0; j < i; j++) b[j] ^= A[j][i];
    }
    return rank; // (rank < m 时有多解)
}
