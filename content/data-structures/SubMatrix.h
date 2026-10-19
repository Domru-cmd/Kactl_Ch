/**
 * 作者:Johan Sannemo
 * 日期:2014-11-28
 * 许可:CC0
 * 来源:民间流传
 * 描述:快速计算子矩阵和,给定左上角与右下角(左闭右开)。
 * 用法:
 * SubMatrix<int> m(matrix);
 * m.sum(0, 0, 2, 2); // 左上角 2x2 的 4 个元素
 * 时间:O(N^2 + Q)
 * 状态:已在 Kattis 上测试
 */
#pragma once

template <class T>
struct SubMatrix {
    vector<vector<T>> p;

    SubMatrix(vector<vector<T>> &v) {
        int R = (int)v.size(), C = (int)v[0].size();
        p.assign(R + 1, vector<T>(C + 1));

        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                p[r + 1][c + 1] = v[r][c] + p[r][c + 1] + p[r + 1][c] - p[r][c];
            }
        }
    }

    T sum(int u, int l, int d, int r) {
        return p[d][r] - p[d][l] - p[u][r] + p[u][l];
    }
};
