/**
 * 作者:Simon Lindholm
 * 日期:2017-05-11
 * 许可:CC0
 * 来源:民间流传
 * 描述:计算 a[i,j](i<I, j<J)的二维前缀和,支持单点加。
 *  要求所有会被更新的位置事先已知(在 init() 前先调用 fakeUpdate())。
 * 时间:O(\log^2 N)。(若要 O(\log N),请使用可持久化线段树。)
 * 状态:已对拍
 */
#pragma once

#include "FenwickTree.h"

struct FT2 {
    vector<vi> ys;
    vector<FT> ft;

    FT2(int limx) : ys(limx) {}

    void fakeUpdate(int x, int y) {
        for (; x < (int)ys.size(); x |= x + 1) {
            ys[x].push_back(y);
        }
    }

    void init() {
        for (vi &v : ys) {
            sort(v.begin(), v.end());
            ft.emplace_back((int)v.size());
        }
    }

    int ind(int x, int y) {
        return (int)(lower_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin());
    }

    void update(int x, int y, ll dif) {
        for (; x < (int)ys.size(); x |= x + 1) {
            ft[x].update(ind(x, y), dif);
        }
    }

    ll query(int x, int y) {
        ll sum = 0;

        for (; x; x &= x - 1) {
            sum += ft[x - 1].query(ind(x - 1, y));
        }

        return sum;
    }
};
