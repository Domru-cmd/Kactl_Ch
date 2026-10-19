/**
 * 作者:Simon Lindholm
 * 许可:CC0
 * 来源:Codeforces
 * 描述:给定 $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$,其中(最小的)
 * 最优 $k$ 随 $i$ 递增,计算 $i = L..R-1$ 的 $a[i]$。
 * 时间:O((N + (hi-lo)) \log N)
 * 状态:在 http://codeforces.com/contest/321/problem/E 上测试
 */
#pragma once

struct DP { // 随意修改:
    int lo(int ind) { return 0; }
    int hi(int ind) { return ind; }
    ll f(int ind, int k) { return dp[ind][k]; }
    void store(int ind, int k, ll v) { res[ind] = pii(k, v); }

    void rec(int L, int R, int LO, int HI) {
        if (L >= R) return;
        int mid = (L + R) >> 1;
        pair<ll, int> best(LLONG_MAX, LO);

        for (int k = max(LO, lo(mid)); k < min(HI, hi(mid)); k++) {
            best = min(best, make_pair(f(mid, k), k));
        }
        store(mid, best.second, best.first);
        rec(L, mid, LO, best.second + 1);
        rec(mid + 1, R, best.second, HI);
    }

    void solve(int L, int R) { rec(L, R, INT_MIN, INT_MAX); }
};
