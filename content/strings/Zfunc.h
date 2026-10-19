/**
 * 作者:chilli
 * 许可:CC0
 * 描述:z[i] 计算 s[i:] 与 s 的最长公共前缀长度,
 * 但 z[0] = 0。(abacaba -> 0010301)
 * 时间:O(n)
 * 状态:已对拍
 */
#pragma once

vi Z(const string &S) {
    vi z((int)S.size());
    int l = -1, r = -1;

    for (int i = 1; i < (int)S.size(); i++) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while (i + z[i] < (int)S.size() && S[i + z[i]] == S[z[i]])
            z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    return z;
}
