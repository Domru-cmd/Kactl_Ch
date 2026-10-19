/**
 * 作者:CodeForces 上的用户 adamant
 * 来源:http://codeforces.com/blog/entry/12143
 * 描述:对字符串的每个位置,计算 p[0][i] = 以 i 为中心的
 *  最长偶回文的半长,p[1][i] = 最长奇回文(半长向下取整)。
 * 时间:O(N)
 * 状态:已对拍
 */
#pragma once

array<vi, 2> manacher(const string &s) {
    int n = (int)s.size();
    array<vi, 2> p = {vi(n + 1), vi(n)};

    for (int z = 0; z < 2; z++) {
        for (int i = 0, l = 0, r = 0; i < n; i++) {
            int t = r - i + !z;
            if (i < r) p[z][i] = min(t, p[z][l + t]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) {
                p[z][i]++;
                L--;
                R++;
            }
            if (R > r) {
                l = L;
                r = R;
            }
        }
    }

    return p;
}
