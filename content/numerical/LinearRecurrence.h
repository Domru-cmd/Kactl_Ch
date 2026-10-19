/**
 * 作者:Lucian Bicsi
 * 日期:2018-02-14
 * 许可:CC0
 * 来源:中文资料
 * 描述:计算 $n$ 阶线性递推 $S[i] = \sum_j S[i-j-1]tr[j]$ 的
 * 第 $k$ 项,给定 $S[0 \ldots \ge n-1]$ 与 $tr[0 \ldots n-1]$。
 * 比矩阵乘法更快。
 * 配合 Berlekamp--Massey 使用效果很好。
 * 用法:linearRec({0, 1}, {1, 1}, k) // 第 k 个斐波那契数
 * 时间:O(n^2 \log k)
 * 状态:在模 5 下对 n <= 5 已暴力验证
 */
#pragma once

const ll mod = 5; /** exclude-line */

using Poly = vector<ll>;
ll linearRec(Poly S, Poly tr, ll k) {
    int n = (int)tr.size();

    auto combine = [&](Poly a, Poly b) {
        Poly res(n * 2 + 1);

        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < n + 1; j++) {
                res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
            }
        }
        for (int i = 2 * n; i > n; i--) {
            for (int j = 0; j < n; j++) {
                res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % mod;
            }
        }
        res.resize(n + 1);
        return res;
    };

    Poly pol(n + 1), e(pol);
    pol[0] = e[1] = 1;

    for (k++; k; k /= 2) {
        if (k % 2) pol = combine(pol, e);
        e = combine(e, e);
    }

    ll res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + pol[i + 1] * S[i]) % mod;
    }

    return res;
}
