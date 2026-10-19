/**
 * 作者:Johan Sannemo, pajenegod
 * 日期:2015-02-06
 * 许可:CC0
 * 来源:民间流传
 * 描述:数组上的静态 RMQ(区间最小值查询)。O(1) 返回
 * min(V[a], V[a + 1], ... V[b - 1])。
 * 用法:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * 时间:O(|V| \log |V| + Q)
 * 状态:已对拍
 */
#pragma once

template <class T>
struct RMQ {
    vector<vector<T>> jmp;

    RMQ(const vector<T> &V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= (int)V.size(); pw *= 2, k++) {
            jmp.emplace_back((int)V.size() - pw * 2 + 1);

            for (int j = 0; j < (int)jmp[k].size(); j++) {
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
        }
    }

    T query(int a, int b) {
        assert(a < b); // a == b 时也可改为返回 inf
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
