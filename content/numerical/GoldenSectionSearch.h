/**
 * 作者:Ulf Lundstrom
 * 日期:2009-04-17
 * 许可:CC0
 * 来源:Numeriska algoritmer med matlab, Gerd Eriksson, NADA, KTH
 * 描述:在区间 $[a,b]$ 上求使函数 $f$ 最小的自变量,假设
 * $f$ 在该区间上单峰,即只有一个局部极小且无局部极大。
 * 结果的最大误差为 $eps$。稍作改动即可用于求最大值。
 * 离散版本见杂项章的 TernarySearch.h。
 * 用法:
	double func(double x) { return 4+x+.3*x*x; }
	double xmin = gss(-1000,1000,func);
 * 时间:O(\log((b-a) / \epsilon))
 * 状态:已测试
 */
#pragma once

/// 保持 r 的精确很重要,否则不能保证 a < x1 < x2 < b。
double gss(double a, double b, double (*f)(double)) {
    double r = (sqrt(5) - 1) / 2, eps = 1e-7;
    double x1 = b - r * (b - a), x2 = a + r * (b - a);
    double f1 = f(x1), f2 = f(x2);

    while (b - a > eps) {
        if (f1 < f2) { // 改成 > 即可求最大值
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = b - r * (b - a);
            f1 = f(x1);
        } else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + r * (b - a);
            f2 = f(x2);
        }
    }

    return a;
}
