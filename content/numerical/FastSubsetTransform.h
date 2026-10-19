/**
 * 作者:Lucian Bicsi
 * 日期:2015-06-25
 * 许可:GNU Free Documentation License 1.2
 * 来源:csacademy
 * 描述:变换到可在如下形式下快速卷积的基:
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * 其中 $\oplus$ 为 AND、OR、XOR 之一。$a$ 的大小必须是 2 的幂。
 * 时间:O(N \log N)
 * 状态:已对拍
 */
#pragma once

void FST(vi &a, bool inv) {
    for (int n = (int)a.size(), step = 1; step < n; step *= 2) {
        for (int i = 0; i < n; i += 2 * step) {
            for (int j = i; j < i + step; j++) {
                int &u = a[j], &v = a[j + step];
                tie(u, v) = inv ? pii(v - u, u) : pii(v, u + v); // AND
                // inv ? pii(v, u - v) : pii(u + v, u); // OR /// include-line
                // pii(u + v, u - v);                   // XOR /// include-line
            }
        }
    }
    // if (inv) for (int& x : a) x /= sz(a); // XOR only /// include-line
}

vi conv(vi a, vi b) {
    FST(a, 0);
    FST(b, 0);
    for (int i = 0; i < (int)a.size(); i++) a[i] *= b[i];
    FST(a, 1);
    return a;
}
