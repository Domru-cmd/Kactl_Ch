/**
 * 作者:Simon Lindholm
 * 日期:2015-02-18
 * 许可:CC0
 * 来源:marian(TC)的代码
 * 描述:Aho-Corasick 自动机,用于多模式匹配。
 * 用 AhoCorasick ac(patterns) 初始化;自动机起点为下标 0。
 * find(word) 对每个位置返回以该位置结尾的最长单词的下标,没有则为 -1。
 * findAll($-$, word) 求出每个位置开始的所有单词(若无重复模式,至多 $N \sqrt N$ 个)
 * (短的在前)。
 * 允许重复模式;不允许空模式。
 * 要求每个位置开始的最长单词,把所有输入反转即可。
 * 对大字符集,把每个符号拆成若干块,块间用哨兵位分隔。
 * 时间:构建 $O(26N)$,$N$ 为模式长度之和。
 * find(x) 为 $O(N)$,$N$ 为 x 的长度。findAll 为 $O(NM)$。
 * 状态:已对拍
 */
#pragma once

struct AhoCorasick {
    enum {alpha = 26, first = 'A'}; // 修改这里!
    struct Node {
        // (nmatches 可选)
        int back, next[alpha], start = -1, end = -1, nmatches = 0;

        Node(int v) { memset(next, v, sizeof(next)); }
    };

    vector<Node> N;
    vi backp;

    void insert(string &s, int j) {
        assert(!s.empty());
        int n = 0;

        for (char c : s) {
            int &m = N[n].next[c - first];
            if (m == -1) {
                n = m = (int)N.size();
                N.emplace_back(-1);
            }
            else n = m;
        }
        if (N[n].end == -1) N[n].start = j;
        backp.push_back(N[n].end);
        N[n].end = j;
        N[n].nmatches++;
    }

    AhoCorasick(vector<string> &pat) : N(1, -1) {
        for (int i = 0; i < (int)pat.size(); i++) insert(pat[i], i);
        N[0].back = (int)N.size();
        N.emplace_back(0);

        queue<int> q;
        for (q.push(0); !q.empty(); q.pop()) {
            int n = q.front(), prev = N[n].back;
            for (int i = 0; i < alpha; i++) {
                int &ed = N[n].next[i], y = N[prev].next[i];
                if (ed == -1) ed = y;
                else {
                    N[ed].back = y;
                    (N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
                        = N[y].end;
                    N[ed].nmatches += N[y].nmatches;
                    q.push(ed);
                }
            }
        }
    }

    vi find(string word) {
        int n = 0;
        vi res; // ll count = 0;

        for (char c : word) {
            n = N[n].next[c - first];
            res.push_back(N[n].end);
            // count += N[n].nmatches;
        }

        return res;
    }

    vector<vi> findAll(vector<string> &pat, string word) {
        vi r = find(word);
        vector<vi> res((int)word.size());

        for (int i = 0; i < (int)word.size(); i++) {
            int ind = r[i];
            while (ind != -1) {
                res[i - (int)pat[ind].size() + 1].push_back(ind);
                ind = backp[ind];
            }
        }

        return res;
    }
};
