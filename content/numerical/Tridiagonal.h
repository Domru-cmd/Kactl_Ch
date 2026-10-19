/**
 * 作者:Ulf Lundstrom, Simon Lindholm
 * 日期:2009-08-15
 * 许可:CC0
 * 来源:https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
 * 描述:$x=\textrm{tridiagonal}(d,p,q,b)$ 求解方程组
\[
\left(\begin{array}{c}b_0\\b_1\\b_2\\b_3\\\vdots\\b_{n-1}\end{array}\right) =
\left(\begin{array}{cccccc}
d_0 & p_0 & 0 & 0 & \cdots & 0\\
q_0 & d_1 & p_1 & 0 & \cdots & 0\\
0 & q_1 & d_2 & p_2 & \cdots & 0\\
\vdots & \vdots & \ddots & \ddots & \ddots & \vdots\\
0 & 0 & \cdots & q_{n-3} & d_{n-2} & p_{n-2}\\
0 & 0 & \cdots & 0 & q_{n-2} & d_{n-1}\\
\end{array}\right)
\left(\begin{array}{c}x_0\\x_1\\x_2\\x_3\\\vdots\\x_{n-1}\end{array}\right).
\]

它可用于求解如下形式的问题
\[ a_i=b_ia_{i-1}+c_ia_{i+1}+d_i,\,1\leq i\leq n, \]
其中 $a_0$, $a_{n+1}$, $b_i$, $c_i$ 与 $d_i$ 已知。此时 $a$ 可由下式得到
\begin{align*}
\{a_i\}=\textrm{tridiagonal}(&\{1,-1,-1,...,-1,1\}, \{0,c_1,c_2,\dots,c_n\},\\
&\{b_1,b_2,\dots,b_n,0\}, \{a_0,d_1,d_2,\dots,d_n,a_{n+1}\}).
\end{align*}
解不唯一时会失败。

若对所有 $i$ 有 $|d_i| > |p_i| + |q_{i-1}|$,或 $|d_i| > |p_{i-1}| + |q_i|$,或矩阵正定,
则算法数值稳定,不再需要 \texttt{tr} 与 \texttt{diag[i] == 0} 的检查。
 * 时间:O(N)
 * 状态:在模 5、7 下暴力验证,并对满足上述条件的实矩阵对拍。
 */
#pragma once

using T = double;
vector<T> tridiagonal(vector<T> diag, const vector<T> &super,
        const vector<T> &sub, vector<T> b) {
    int n = (int)b.size();
    vi tr(n);

    for (int i = 0; i < n - 1; i++) {
        if (abs(diag[i]) < 1e-9 * abs(super[i])) { // diag[i] == 0
            b[i + 1] -= b[i] * diag[i + 1] / super[i];
            if (i + 2 < n) b[i + 2] -= b[i] * sub[i + 1] / super[i];
            diag[i + 1] = sub[i];
            tr[++i] = 1;
        } else {
            diag[i + 1] -= super[i] * sub[i] / diag[i];
            b[i + 1] -= b[i] * sub[i] / diag[i];
        }
    }
    for (int i = n; i--;) {
        if (tr[i]) {
            swap(b[i], b[i - 1]);
            diag[i - 1] = diag[i];
            b[i] /= super[i - 1];
        } else {
            b[i] /= diag[i];
            if (i) b[i - 1] -= b[i] * super[i - 1];
        }
    }

    return b;
}
