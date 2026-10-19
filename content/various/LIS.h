/**
 * 作者:Johan Sannemo
 * 许可:CC0
 * 描述:计算最长上升子序列的下标。
 * 时间:$O(N \log N)$
 * 状态:在 kattis:longincsubseq 上测试,已对拍
 */
#pragma once

template <class I>
vi lis(const vector<I> &S) {
    if (S.empty()) return {};
    vi prev((int)S.size());
    using p = pair<I, int>;
    vector<p> res;

    for (int i = 0; i < (int)S.size(); i++) {
        // 改成 i 即为最长不降子序列
        auto it = lower_bound(res.begin(), res.end(), p{S[i], 0});
        if (it == res.end()) {
            res.emplace_back();
            it = res.end() - 1;
        }
        *it = {S[i], i};
        prev[i] = it == res.begin() ? 0 : (it - 1)->second;
    }
    int L = (int)res.size(), cur = res.back().second;
    vi ans(L);

    while (L--) {
        ans[L] = cur;
        cur = prev[cur];
    }

    return ans;
}
