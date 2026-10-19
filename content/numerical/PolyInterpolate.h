/**
 * 作者:Simon Lindholm
 * 日期:2017-05-10
 * 许可:CC0
 * 来源:Wikipedia
 * 描述:给定 $n$ 个点 (x[i], y[i]),计算过这些点的
 *  n-1 次多项式 $p$:$p(x) = a[0]*x^0 + ... + a[n-1]*x^{n-1}$。
 *  为了数值精度,取 $x[k] = c*\cos(k/(n-1)*\pi), k=0 \dots n-1$。
 * 时间:O(n^2)
 */
#pragma once

using vd = vector<double>;
vd interpolate(vd x, vd y, int n) {
    vd res(n), temp(n);

    for (int k = 0; k < n - 1; k++) {
        for (int i = k + 1; i < n; i++) {
            y[i] = (y[i] - y[k]) / (x[i] - x[k]);
        }
    }
    double last = 0;
    temp[0] = 1;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            res[i] += y[k] * temp[i];
            swap(last, temp[i]);
            temp[i] -= last * x[k];
        }
    }

    return res;
}
