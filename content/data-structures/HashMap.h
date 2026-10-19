/**
 * 作者:Simon Lindholm, chilli
 * 日期:2018-07-23
 * 许可:CC0
 * 来源:http://codeforces.com/blog/entry/60737
 * 描述:与 unordered\_map 接口基本一致的哈希表,速度约为其 3 倍,
 * 内存占用为其 1.5 倍。
 * 初始容量必须为 2 的幂(若提供)。
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
// 为了尽量利用高位而不是低位:
struct chash { // C 取大的奇数
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};
__gnu_pbds::gp_hash_table<ll, int, chash> h({}, {}, {}, {}, {1 << 16});

/** 用于 CodeForces 等比赛可能被卡哈希的场合:

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { // 为了尽量利用高位而不是低位:
    const uint64_t C = ll(4e18 * acos(0)) | 71; // 大的奇数
    ll operator()(ll x) const { return __builtin_bswap64((x^RANDOM)*C); }
};
__gnu_pbds::gp_hash_table<ll, int, chash> h({},{},{},{}, {1 << 16});
*/
