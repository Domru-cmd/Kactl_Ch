/**
 * 作者:Simon Lindholm
 * 日期:2016-12-08
 * 来源:常规矩阵求逆代码
 * 描述:求矩阵 $A$ 模一个素数的逆。
 * 返回秩;除非奇异(rank < n),结果存入 $A$。
 * 对素数幂,反复令 $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$,其中 $A^{-1}$ 初值
 * 为 A 模 p 的逆,k 每步翻倍。
 * 时间:O(n^3)
 * 状态:轻度测试
 */
#pragma once

#include "../number-theory/ModPow.h"

int matInv(vector<vector<ll>> &A) {
    int n = (int)A.size();
    vi col(n);
    vector<vector<ll>> tmp(n, vector<ll>(n));

    for (int i = 0; i < n; i++) {
        tmp[i][i] = 1;
        col[i] = i;
    }

    for (int i = 0; i < n; i++) {
        int r = i, c = i;
        for (int j = i; j < n; j++) {
            for (int k = i; k < n; k++) {
                if (A[j][k]) {
                    r = j;
                    c = k;
                    goto found;
                }
            }
        }
        return i;
found:
        A[i].swap(A[r]);
        tmp[i].swap(tmp[r]);
        for (int j = 0; j < n; j++) {
            swap(A[j][i], A[j][c]);
            swap(tmp[j][i], tmp[j][c]);
        }
        swap(col[i], col[c]);
        ll v = modpow(A[i][i], mod - 2);
        for (int j = i + 1; j < n; j++) {
            ll f = A[j][i] * v % mod;
            A[j][i] = 0;
            for (int k = i + 1; k < n; k++) A[j][k] = (A[j][k] - f * A[i][k]) % mod;
            for (int k = 0; k < n; k++) tmp[j][k] = (tmp[j][k] - f * tmp[i][k]) % mod;
        }
        for (int j = i + 1; j < n; j++) A[i][j] = A[i][j] * v % mod;
        for (int j = 0; j < n; j++) tmp[i][j] = tmp[i][j] * v % mod;
        A[i][i] = 1;
    }

    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            ll v = A[j][i];
            for (int k = 0; k < n; k++) tmp[j][k] = (tmp[j][k] - v * tmp[i][k]) % mod;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            A[col[i]][col[j]] = tmp[i][j] % mod + (tmp[i][j] < 0) * mod;
    }

    return n;
}
