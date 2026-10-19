/**
 * 作者:chilli
 * 日期:2019-04-16
 * 许可:CC0
 * 来源:基于 KACTL 的 FFT
 * 描述:ntt(a) 对所有 $k$ 计算 $\hat f(k) = \sum_x a[x] g^{xk}$,其中 $g=\text{root}^{(mod-1)/N}$。
 * N 必须是 2 的幂。
 * 适用于形如 $2^a b+1$ 的特定素数的卷积,此时卷积结果大小至多 $2^a$。
 * 任意模数见 FFTMod。
 *   \texttt{conv(a, b) = c},其中 $c[x] = \sum a[i]b[x-i]$。
 *   手动卷积:对输入做 NTT,逐点相乘,除以 n,
 *   反转(start+1, end),再做 NTT 变回。
 * 输入必须在 [0, mod) 内。
 * 时间:O(N \log N)
 * 状态:已对拍
 */
#pragma once

#include "../number-theory/ModPow.h"

const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// 对 p < 2^30 还有例如 5 << 25、7 << 26、479 << 21
// 以及 483 << 21(同根)。后两个 > 10^9。
using vl = vector<ll>;
void ntt(vl &a) {
    int n = (int)a.size(), L = 31 - __builtin_clz(n);
    static vl rt(2, 1);

    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        ll z[] = {1, modpow(root, mod >> s)};

        for (int i = k; i < 2 * k; i++) rt[i] = rt[i / 2] * z[i & 1] % mod;
    }
    vi rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i = 0; i < n; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
                a[i + j + k] = ai - z + (z > ai ? mod : 0);
                ai += (ai + z >= mod ? z - mod : z);
            }
        }
    }
}

vl conv(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    int s = (int)a.size() + (int)b.size() - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    int inv = modpow(n, mod - 2);
    vl L(a), R(b), out(n);
    L.resize(n);
    R.resize(n);
    ntt(L);
    ntt(R);

    for (int i = 0; i < n; i++) {
        out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
    }
    ntt(out);
    return {out.begin(), out.begin() + s};
}
