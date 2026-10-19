/**
 * 作者:Ludo Pulles, chilli, Simon Lindholm
 * 日期:2019-01-09
 * 许可:CC0
 * 来源:http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf(很值得一读)
   精度界来自 http://www.daemonology.net/papers/fft.pdf
 * 描述:fft(a) 对所有 $k$ 计算 $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$。N 必须是 2 的幂。
   用于卷积:
   \texttt{conv(a, b) = c},其中 $c[x] = \sum a[i]b[x-i]$。
   复数或多个向量的卷积:先 FFT,逐点相乘,除以 n,
   反转(start+1, end),再 FFT 变换回去。
   若 $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$,
   舍入是安全的(实际中 $10^{16}$;随机输入更高)。
   否则,请使用 NTT/FFTMod。
 * 时间:O(N \log N),$N = |A|+|B|$($N=2^{22}$ 时约 1s)
 * 状态:部分测试
 * 细节:FFT 与 FFTMod 精度的深入分析见
 * (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

using C = complex<double>;
using vd = vector<double>;
void fft(vector<C> &a) {
    int n = (int)a.size(), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1); // (^ 用 double 快 10%)

    for (static int k = 2; k < n; k *= 2) {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);

        for (int i = k; i < 2 * k; i++) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vi rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i = 0; i < n; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                // C z = rt[j+k] * a[i+j+k]; // (手工展开可快 25%)  /// include-line
                auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k];   /// exclude-line
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);    /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
}

vd conv(const vd &a, const vd &b) {
    if (a.empty() || b.empty()) return {};
    vd res((int)a.size() + (int)b.size() - 1);
    int L = 32 - __builtin_clz((int)res.size()), n = 1 << L;
    vector<C> in(n), out(n);
    copy(a.begin(), a.end(), in.begin());
    for (int i = 0; i < (int)b.size(); i++) in[i].imag(b[i]);
    fft(in);
    for (C &x : in) x *= x;
    for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    for (int i = 0; i < (int)res.size(); i++) res[i] = imag(out[i]) / (4 * n);
    return res;
}
