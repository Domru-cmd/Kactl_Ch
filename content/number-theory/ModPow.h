/**
 * 作者:Noam527
 * 日期:2019-04-24
 * 许可:CC0
 * 来源:民间流传
 * 描述:快速幂取模。
 * 状态:已测试
 */
#pragma once

const ll mod = 1000000007; // 用 const 会更快

ll modpow(ll b, ll e) {
    ll ans = 1;

    for (; e; b = b * b % mod, e /= 2) {
        if (e & 1) ans = ans * b % mod;
    }

    return ans;
}
