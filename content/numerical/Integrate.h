/**
 * 作者:Simon Lindholm
 * 日期:2015-02-11
 * 许可:CC0
 * 来源:Wikipedia
 * 描述:使用 Simpson 法则在区间上对函数做简单积分。
 *  误差应与 $h^4$ 成正比,不过实际中你会想验证:当 epsilon
 *  变化时结果在所需精度内保持稳定。
 * 状态:基本未测试
 */
#pragma once

template <class F>
double quad(double a, double b, F f, const int n = 1000) {
    double h = (b - a) / 2 / n, v = f(a) + f(b);

    for (int i = 1; i < n * 2; i++) {
        v += f(a + i * h) * (i & 1 ? 4 : 2);
    }

    return v * h / 3;
}
