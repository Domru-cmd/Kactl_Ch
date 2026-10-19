/**
 * 作者:Per Austrin, Simon Lindholm
 * 日期:2004-02-08
 * 许可:CC0
 * 描述:解 $A * x = b$。若有多解,返回任意一个。
 *  返回秩;无解则返回 -1。$A$ 与 $b$ 中的数据会被破坏。
 * 时间:O(n^2 m)
 * 状态:在 kattis:equationsolver 上测试,并在模 3、5 下对 n,m <= 3 暴力验证
 */
#pragma once

using vd = vector<double>;
const double eps = 1e-12;

int solveLinear(vector<vd> &A, vd &b, vd &x) {
    int n = (int)A.size(), m = (int)x.size(), rank = 0, br, bc;
    if (n) assert((int)A[0].size() == m);
    vi col(m);
    iota(col.begin(), col.end(), 0);

    for (int i = 0; i < n; i++) {
        double v, bv = 0;
        for (int r = i; r < n; r++) {
            for (int c = i; c < m; c++) {
                if ((v = fabs(A[r][c])) > bv) {
                    br = r;
                    bc = c;
                    bv = v;
                }
            }
        }
        if (bv <= eps) {
            for (int j = i; j < n; j++) {
                if (fabs(b[j]) > eps) return -1;
            }
            break;
        }
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        for (int j = 0; j < n; j++) swap(A[j][i], A[j][bc]);
        bv = 1 / A[i][i];
        for (int j = i + 1; j < n; j++) {
            double fac = A[j][i] * bv;
            b[j] -= fac * b[i];
            for (int k = i + 1; k < m; k++) A[j][k] -= fac * A[i][k];
        }
        rank++;
    }

    x.assign(m, 0);
    for (int i = rank; i--;) {
        b[i] /= A[i][i];
        x[col[i]] = b[i];
        for (int j = 0; j < i; j++) b[j] -= A[j][i] * b[i];
    }
    return rank; // (rank < m 时有多解)
}
