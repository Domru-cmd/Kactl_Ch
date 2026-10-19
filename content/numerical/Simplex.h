/**
 * 作者:Stanford
 * 来源:Stanford Notebook
 * 许可:MIT
 * 描述:求解一般线性最大化问题:最大化 $c^T x$,约束 $Ax \le b$,$x \ge 0$。
 * 无解返回 -inf,有任意好的解返回 inf,否则返回 $c^T x$ 的最大值。
 * 输入向量会被设为最优的 $x$(无界时,为满足约束的任意解)。
 * 不保证数值稳定性。为获得更好性能,定义变量时让 $x = 0$ 可行。
 * 用法:
 * vvd A = {{1,-1}, {-1,1}, {-1,-2}};
 * vd b = {1,1,-4}, c = {-1,-1}, x;
 * T val = LPSolver(A, b, c).solve(x);
 * 时间:O(NM * \#pivots),一次 pivot 例如一次边松弛。一般情况下为 O(2^n)。
 * 状态:似乎可用?
 */
#pragma once

using T = double; // long double、Rational、double + mod<P>……
using vd = vector<T>;
using vvd = vector<vd>;

const T eps = 1e-8, inf = 1 / .0;
#define MP make_pair
#define ltj(X) if (s == -1 || MP(X[j], N[j]) < MP(X[s], N[s])) s = j

struct LPSolver {
    int m, n;
    vi N, B;
    vvd D;

    LPSolver(const vvd &A, const vd &b, const vd &c) :
        m((int)b.size()), n((int)c.size()), N(n + 1), B(m), D(m + 2, vd(n + 2)) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        }
        for (int i = 0; i < m; i++) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }

    void pivot(int r, int s) {
        T *a = D[r].data(), inv = 1 / a[s];
        for (int i = 0; i < m + 2; i++) {
            if (i != r && abs(D[i][s]) > eps) {
                T *b = D[i].data(), inv2 = b[s] * inv;
                for (int j = 0; j < n + 2; j++) b[j] -= a[j] * inv2;
                b[s] = a[s] * inv2;
            }
        }
        for (int j = 0; j < n + 2; j++) {
            if (j != s) D[r][j] *= inv;
        }
        for (int i = 0; i < m + 2; i++) {
            if (i != r) D[i][s] *= -inv;
        }
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool simplex(int phase) {
        int x = m + phase - 1;
        for (;;) {
            int s = -1;
            for (int j = 0; j < n + 1; j++) {
                if (N[j] != -phase) ltj(D[x]);
            }
            if (D[x][s] >= -eps) return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] <= eps) continue;
                if (r == -1 || MP(D[i][n + 1] / D[i][s], B[i])
                             < MP(D[r][n + 1] / D[r][s], B[r])) r = i;
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }

    T solve(vd &x) {
        int r = 0;
        for (int i = 1; i < m; i++) {
            if (D[i][n + 1] < D[r][n + 1]) r = i;
        }
        if (D[r][n + 1] < -eps) {
            pivot(r, n);
            if (!simplex(2) || D[m + 1][n + 1] < -eps) return -inf;
            for (int i = 0; i < m; i++) {
                if (B[i] == -1) {
                    int s = 0;
                    for (int j = 1; j < n + 1; j++) ltj(D[i]);
                    pivot(i, s);
                }
            }
        }
        bool ok = simplex(1);
        x = vd(n);
        for (int i = 0; i < m; i++) {
            if (B[i] < n) x[B[i]] = D[i][n + 1];
        }
        return ok ? D[m][n + 1] : inf;
    }
};
