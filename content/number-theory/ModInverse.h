/**
 * 作者:Simon Lindholm
 * 日期:2016-07-24
 * 许可:CC0
 * 来源:俄文页面
 * 描述:模逆元的预处理。假设 LIM <= mod,且 mod 是素数。
 * 状态:可用
 */
#pragma once

// const ll mod = 1000000007, LIM = 200000; ///include-line
ll *inv = new ll[LIM] - 1;
inv[1] = 1;

for (int i = 2; i < LIM; i++) {
    inv[i] = mod - (mod / i) * inv[mod % i] % mod;
}
