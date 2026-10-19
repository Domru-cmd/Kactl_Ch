/**
 * 作者:Stjepan Glavina
 * 许可:Unlicense
 * 来源:https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * 描述:求字符串字典序最小的循环移位。
 * 时间:O(N)
 * 用法:
 *  rotate(v.begin(), v.begin()+minRotation(v), v.end());
 * 状态:已对拍
 */
#pragma once

int minRotation(string s) {
    int a = 0, N = (int)s.size();
    s += s;

    for (int b = 0; b < N; b++) {
        for (int k = 0; k < N; k++) {
            if (a + k == b || s[a + k] < s[b + k]) {
                b += max(0, k - 1);
                break;
            }
            if (s[a + k] > s[b + k]) {
                a = b;
                break;
            }
        }
    }

    return a;
}
