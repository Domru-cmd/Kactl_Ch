/**
 * 作者:佚名
 * 日期:2017-05-15
 * 来源:https://e-maxx.ru/algo/ukkonen
 * 描述:在线构建后缀树的 Ukkonen 算法。
 *  每个节点保存字符串中的下标区间 [l, r) 以及子节点列表。
 *  后缀由遍历该树、连接 [l, r) 子串得到。
 *  根为 0(l = -1, r = 0),不存在的子节点为 -1。
 *  要得到完整的树,在末尾附加一个哑符号——否则可能包含
 *  未完整的路径(不过对子串匹配仍然有用)。
 * 时间:$O(26N)$
 * 状态:已部分对拍
 */
#pragma once

struct SuffixTree {
    enum { N = 200010, ALPHA = 26 }; // N ~ 2*maxlen+10
    int toi(char c) { return c - 'a'; }
    string a; // v = 当前节点,q = 当前位置
    int t[N][ALPHA], l[N], r[N], p[N], s[N], v = 0, q = 0, m = 2;

    void ukkadd(int i, int c) {
suff:
        if (r[v] <= q) {
            if (t[v][c] == -1) {
                t[v][c] = m;
                l[m] = i;
                p[m++] = v;
                v = s[v];
                q = r[v];
                goto suff;
            }
            v = t[v][c];
            q = l[v];
        }
        if (q == -1 || c == toi(a[q])) q++;
        else {
            l[m + 1] = i;
            p[m + 1] = m;
            l[m] = l[v];
            r[m] = q;
            p[m] = p[v];
            t[m][c] = m + 1;
            t[m][toi(a[q])] = v;
            l[v] = q;
            p[v] = m;
            t[p[m]][toi(a[l[m]])] = m;
            v = s[p[m]];
            q = l[m];

            while (q < r[m]) {
                v = t[v][toi(a[q])];
                q += r[v] - l[v];
            }
            if (q == r[m]) s[m] = v;
            else s[m] = m + 2;
            q = r[v] - (q - r[m]);
            m += 2;
            goto suff;
        }
    }

    SuffixTree(string a) : a(a) {
        fill(r, r + N, (int)a.size());
        memset(s, 0, sizeof s);
        memset(t, -1, sizeof t);
        fill(t[1], t[1] + ALPHA, 0);
        s[0] = 1;
        l[0] = l[1] = -1;
        r[0] = r[1] = p[0] = p[1] = 0;
        for (int i = 0; i < (int)a.size(); i++) ukkadd(i, toi(a[i]));
    }

    // 示例:求最长公共子串(使用 ALPHA = 28)
    pii best;
    int lcs(int node, int i1, int i2, int olen) {
        if (l[node] <= i1 && i1 < r[node]) return 1;
        if (l[node] <= i2 && i2 < r[node]) return 2;
        int mask = 0, len = node ? olen + (r[node] - l[node]) : 0;

        for (int c = 0; c < ALPHA; c++) {
            if (t[node][c] != -1)
                mask |= lcs(t[node][c], i1, i2, len);
        }
        if (mask == 3)
            best = max(best, {len, r[node] - len});
        return mask;
    }

    static pii LCS(string s, string t) {
        SuffixTree st(s + (char)('z' + 1) + t + (char)('z' + 2));
        st.lcs(0, (int)s.size(), (int)s.size() + 1 + (int)t.size(), 0);
        return st.best;
    }
};
