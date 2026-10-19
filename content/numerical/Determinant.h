/**
 * 作者:Simon Lindholm
 * 日期:2016-09-06
 * 许可:CC0
 * 来源:民间流传
 * 描述:计算矩阵的行列式。会破坏矩阵。
 * 时间:$O(N^3)$
 * 状态:部分测试
 */
#pragma once

double det(vector<vector<double>> &a) {
    int n = (int)a.size();
    double res = 1;

    for (int i = 0; i < n; i++) {
        int b = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(a[j][i]) > fabs(a[b][i])) b = j;
        }
        if (i != b) {
            swap(a[i], a[b]);
            res *= -1;
        }
        res *= a[i][i];
        if (res == 0) return 0;
        for (int j = i + 1; j < n; j++) {
            double v = a[j][i] / a[i][i];
            if (v != 0) {
                for (int k = i + 1; k < n; k++) a[j][k] -= v * a[i][k];
            }
        }
    }

    return res;
}
