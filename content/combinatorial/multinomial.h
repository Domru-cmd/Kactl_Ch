/**
 * 作者:Mattias de Zalenski, Fredrik Niemelä, Per Austrin, Simon Lindholm
 * 日期:2002-09-26
 * 来源:Max Bennedich
 * 描述:计算 $\displaystyle \binom{k_1 + \dots + k_n}{k_1, k_2, \dots, k_n} = \frac{(\sum k_i)!}{k_1!k_2!\cdots k_n!}$。
 * 状态:在 kattis:lexicography 上测试
 */
#pragma once

ll multinomial(vi &v) {
    ll c = 1, m = v.empty() ? 1 : v[0];

    for (int i = 1; i < (int)v.size(); i++) {
        for (int j = 0; j < v[i]; j++) {
            c = c * ++m / (j + 1);
        }
    }

    return c;
}
