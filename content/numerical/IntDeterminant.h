/**
 * 作者:佚名
 * 日期:2014-11-27
 * 来源:github 上的某处
 * 描述:使用模运算计算行列式。
 * 去掉取模即可得到纯整数版本。
 * 时间:$O(N^3)$
 * 状态:对 N <= 3, mod <= 7 已暴力验证
 */
#pragma once

const ll mod = 12345;
ll det(vector<vector<ll>> &a) {
    int n = (int)a.size();
    ll ans = 1;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            while (a[j][i] != 0) { // gcd 步骤
                ll t = a[i][i] / a[j][i];
                if (t) {
                    for (int k = i; k < n; k++)
                        a[i][k] = (a[i][k] - a[j][k] * t) % mod;
                }
                swap(a[i], a[j]);
                ans *= -1;
            }
        }
        ans = ans * a[i][i] % mod;
        if (!ans) return 0;
    }

    return (ans + mod) % mod;
}
