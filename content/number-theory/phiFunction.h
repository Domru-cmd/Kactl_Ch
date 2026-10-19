/**
 * 作者:Håkan Terelius
 * 日期:2009-09-25
 * 许可:CC0
 * 来源:http://en.wikipedia.org/wiki/Euler's_totient_function
 * 描述:\emph{欧拉 $\phi$ 函数}定义为 $\phi(n):=$ 不超过 $n$ 且与 $n$ 互素的正整数个数。
 * $\phi(1)=1$,$p$ 为素数 $\Rightarrow \phi(p^k)=(p-1)p^{k-1}$,$m,n$ 互素 $\Rightarrow \phi(mn)=\phi(m)\phi(n)$。
 * 若 $n=p_1^{k_1}p_2^{k_2} ... p_r^{k_r}$,则 $\phi(n) = (p_1-1)p_1^{k_1-1}...(p_r-1)p_r^{k_r-1}$。
 * $\phi(n)=n \cdot \prod_{p|n}(1-1/p)$。
 *
 * $\sum_{d|n} \phi(d) = n$,$\sum_{1\leq k \leq n, \gcd(k,n)=1} k = n \phi(n)/2, n>1$
 *
 * \textbf{欧拉定理}:$a,n$ 互素 $\Rightarrow a^{\phi(n)} \equiv 1 \pmod{n}$。
 *
 * \textbf{费马小定理}:$p$ 为素数 $\Rightarrow a^{p-1} \equiv 1 \pmod{p}$ $\forall a$。
 * 状态:已测试
 */
#pragma once

const int LIM = 5000000;
int phi[LIM];

void calculatePhi() {
    for (int i = 0; i < LIM; i++) {
        phi[i] = i & 1 ? i : i / 2;
    }

    for (int i = 3; i < LIM; i += 2) {
        if (phi[i] == i) {
            for (int j = i; j < LIM; j += i) phi[j] -= phi[j] / i;
        }
    }
}
