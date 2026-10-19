/**
 * 作者:Jakob Kogler, chilli, pajenegod
 * 日期:2020-04-12
 * 许可:CC0
 * 描述:生成小于 LIM 的所有素数的筛法。
 * 时间:LIM=1e9 约 1.5s
 * 状态:已对拍
 * 细节:尽管复杂度是 n log log n,分段筛仍然比其它方案
 * (包括 bitset 筛与线性筛)更快。这主要归功于低内存占用
 * 带来的更少缓存缺失。本实现跳过偶数。
 *
 * 基准见:https://ideone.com/e7TbX4
 *
 * `for (int i=idx; i<S+L; idx = (i += p))` 这一行是出于性能原因故意这么写的。
 * 见 https://github.com/kth-competitive-programming/kactl/pull/166#discussion_r408354338
 */
#pragma once

const int LIM = 1e6;
bitset<LIM> isPrime;

vi eratosthenes() {
    const int S = (int)round(sqrt(LIM)), R = LIM / 2;
    vi pr = {2}, sieve(S + 1);
    pr.reserve(int(LIM / log(LIM) * 1.1));
    vector<pii> cp;

    for (int i = 3; i <= S; i += 2) {
        if (!sieve[i]) {
            cp.push_back({i, i * i / 2});
            for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
        }
    }

    for (int L = 1; L <= R; L += S) {
        array<bool, S> block{};
        for (auto &[p, idx] : cp) {
            for (int i = idx; i < S + L; idx = (i += p)) block[i - L] = 1;
        }

        for (int i = 0; i < min(S, R - L); i++) {
            if (!block[i]) pr.push_back((L + i) * 2 + 1);
        }
    }

    for (int i : pr) isPrime[i] = 1;
    return pr;
}
