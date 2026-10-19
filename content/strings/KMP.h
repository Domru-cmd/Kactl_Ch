/**
 * 作者:Johan Sannemo
 * 日期:2016-12-15
 * 许可:CC0
 * 描述:pi[x] 计算 s 中以 x 结尾的最长真前缀(不含 s[0...x] 本身)的长度
 * (abacaba -> 0010123)。
 * 可用于求一个串的全部出现位置。
 * 时间:O(n)
 * 状态:在 kattis:stringmatching 上测试
 */
#pragma once

vi pi(const string &s) {
    vi p((int)s.size());

    for (int i = 1; i < (int)s.size(); i++) {
        int g = p[i - 1];
        while (g && s[i] != s[g]) g = p[g - 1];
        p[i] = g + (s[i] == s[g]);
    }

    return p;
}

vi match(const string &s, const string &pat) {
    vi p = pi(pat + '\0' + s), res;

    for (int i = (int)p.size() - (int)s.size(); i < (int)p.size(); i++) {
        if (p[i] == (int)pat.size()) res.push_back(i - 2 * (int)pat.size());
    }

    return res;
}
