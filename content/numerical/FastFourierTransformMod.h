/**
 * 作者:chilli
 * 日期:2019-04-25
 * 许可:CC0
 * 来源:http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * 描述:更高精度的 FFT,可用于任意整数的卷积,
 * 只要 $N\log_2N\cdot \text{mod} < 8.6 \cdot 10^{14}$(实际中 $10^{16}$ 或更高也行)。
 * 输入必须在 $[0, \text{mod})$ 内。
 * 时间:O(N \log N),其中 $N = |A|+|B|$(比 NTT 或 FFT 慢一倍)
 * 状态:已对拍
 * 细节:FFT 与 FFTMod 精度的深入分析见
 * (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

#include "FastFourierTransform.h"

using vl = vector<ll>;
template <int M>
vl convMod(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    vl res((int)a.size() + (int)b.size() - 1);
    int B = 32 - __builtin_clz((int)res.size()), n = 1 << B, cut = int(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);

    for (int i = 0; i < (int)a.size(); i++) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
    for (int i = 0; i < (int)b.size(); i++) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
    fft(L);
    fft(R);

    for (int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl);
    fft(outs);

    for (int i = 0; i < (int)res.size(); i++) {
        ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
        ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }

    return res;
}
