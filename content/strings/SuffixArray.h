/**
 * 作者:罗穗骞, chilli
 * 日期:2019-04-11
 * 许可:未知
 * 来源:后缀数组——处理字符串的有力工具
 * (中国国家集训队论文,2009)
 * 描述:构建字符串的后缀数组。
 * \texttt{sa[i]} 为排名第 $i$ 的后缀的起始下标。
 * 返回的 vector 大小为 $n+1$,且 \texttt{sa[0] = n}。
 * \texttt{lcp} 数组包含后缀数组中相邻后缀的最长公共前缀:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])},\texttt{lcp[0] = 0}。
 * 输入字符串不能含 nul 字符。
 * 时间:O(n \log n)
 * 状态:已对拍
 */
#pragma once

struct SuffixArray {
    vi sa, lcp;

    SuffixArray(string s, int lim = 256) { // 或 vector<int>
        s.push_back(0);
        int n = (int)s.size(), k = 0, a, b;
        vi x(s.begin(), s.end()), y(n), ws(max(n, lim));
        sa = lcp = y;
        iota(sa.begin(), sa.end(), 0);

        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j;
            iota(y.begin(), y.end(), n - j);

            for (int i = 0; i < n; i++) {
                if (sa[i] >= j) y[p++] = sa[i] - j;
            }
            fill(ws.begin(), ws.end(), 0);
            for (int i = 0; i < n; i++) ws[x[i]]++;
            for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
            for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                a = sa[i - 1];
                b = sa[i];
                x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
        }

        for (int i = 0, j; i < n - 1; lcp[x[i++]] = k) {
            for (k && k--, j = sa[x[i] - 1];
                    s[i + k] == s[j + k]; k++);
        }
    }
};
