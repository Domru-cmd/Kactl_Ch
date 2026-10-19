/**
 * 作者:Johan Sannemo
 * 日期:2017-04-18
 * 来源:改自 Mark Gordon 的 https://gist.github.com/msg555/4963794
 * 描述:计算点集三维凸包的全部面。
 *  *任意四点都不能共面*,否则结果随机。
 *  所有面均朝外。
 * 时间:O(n^2)
 * 状态:在 SPOJ CH3D 上测试
 */
#pragma once

#include "Point3D.h"

using P3 = Point3D<double>;

struct PR {
    void ins(int x) { (a == -1 ? a : b) = x; }
    void rem(int x) { (a == x ? a : b) = -1; }
    int cnt() { return (a != -1) + (b != -1); }
    int a, b;
};

struct F { P3 q; int a, b, c; };

vector<F> hull3d(const vector<P3> &A) {
    assert((int)A.size() >= 4);
    vector<vector<PR>> E((int)A.size(), vector<PR>((int)A.size(), {-1, -1}));
#define E(x,y) E[f.x][f.y]
    vector<F> FS;

    auto mf = [&](int i, int j, int k, int l) {
        P3 q = (A[j] - A[i]).cross((A[k] - A[i]));
        if (q.dot(A[l]) > q.dot(A[i]))
            q = q * -1;
        F f{q, i, j, k};
        E(a, b).ins(k);
        E(a, c).ins(j);
        E(b, c).ins(i);
        FS.push_back(f);
    };

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            for (int k = j + 1; k < 4; k++) {
                mf(i, j, k, 6 - i - j - k);
            }
        }
    }

    for (int i = 4; i < (int)A.size(); i++) {
        for (int j = 0; j < (int)FS.size(); j++) {
            F f = FS[j];
            if (f.q.dot(A[i]) > f.q.dot(A[f.a])) {
                E(a, b).rem(f.c);
                E(a, c).rem(f.b);
                E(b, c).rem(f.a);
                swap(FS[j--], FS.back());
                FS.pop_back();
            }
        }
        int nw = (int)FS.size();

        for (int j = 0; j < nw; j++) {
            F f = FS[j];
#define C(a, b, c) if (E(a,b).cnt() != 2) mf(f.a, f.b, i, f.c);
            C(a, b, c);
            C(a, c, b);
            C(b, c, a);
        }
    }
    for (F &it : FS) {
        if ((A[it.b] - A[it.a]).cross(
            A[it.c] - A[it.a]).dot(it.q) <= 0) swap(it.c, it.b);
    }

    return FS;
}
