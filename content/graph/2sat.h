/**
 * 作者:Emil Lenngren, Simon Lindholm
 * 日期:2011-11-29
 * 许可:CC0
 * 来源:民间流传
 * 描述:为 2-SAT 问题的布尔变量 a, b, c,... 计算一个合法赋值,
 * 使形如 $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$ 的表达式
 * 为真,或报告其不可满足。
 * 取反的变量用按位取反表示(\texttt{\tilde{}x})。
 * 用法:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // 变量 0 为真或变量 3 为假
 *  ts.setValue(2); // 变量 2 为真
 *  ts.atMostOne({0,\tilde1,2}); // 0、\tilde1、2 中至多一个为真
 *  ts.solve(); // 可满足时返回 true
 *  ts.values[0..N-1] 保存各变量的赋值
 * 时间:O(N+E),其中 N 为布尔变量数,E 为子句数。
 * 状态:已对拍
 */
#pragma once

struct TwoSat {
    int N;
    vector<vi> gr;
    vi values; // 0 = false, 1 = true

    TwoSat(int n = 0) : N(n), gr(2 * n) {}

    int addVar() { // (可选)
        gr.emplace_back();
        gr.emplace_back();
        return N++;
    }

    void either(int f, int j) {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        gr[f].push_back(j ^ 1);
        gr[j].push_back(f ^ 1);
    }

    void setValue(int x) { either(x, x); }

    void atMostOne(const vi &li) { // (可选)
        if ((int)li.size() <= 1) return;
        int cur = ~li[0];

        for (int i = 2; i < (int)li.size(); i++) {
            int next = addVar();
            either(cur, ~li[i]);
            either(cur, next);
            either(~li[i], next);
            cur = ~next;
        }
        either(cur, ~li[1]);
    }

    vi val, comp, z;
    int time = 0;

    int dfs(int i) {
        int low = val[i] = ++time, x;
        z.push_back(i);
        for (int e : gr[i]) {
            if (!comp[e])
                low = min(low, val[e] ? val[e] : dfs(e));
        }
        if (low == val[i]) {
            do {
                x = z.back();
                z.pop_back();
                comp[x] = low;
                if (values[x >> 1] == -1)
                    values[x >> 1] = x & 1;
            } while (x != i);
        }
        return val[i] = low;
    }

    bool solve() {
        values.assign(N, -1);
        val.assign(2 * N, 0);
        comp = val;
        for (int i = 0; i < 2 * N; i++) {
            if (!comp[i]) dfs(i);
        }
        for (int i = 0; i < N; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return 0;
        }
        return 1;
    }
};
