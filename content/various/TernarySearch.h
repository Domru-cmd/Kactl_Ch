/**
 * 作者:Simon Lindholm
 * 日期:2015-05-12
 * 许可:CC0
 * 来源:自己整理
 * 描述:
 * 求 $[a,b]$ 中使 $f(i)$ 最大的最小 i,假设 $f(a) < \dots < f(i) \ge \dots \ge f(b)$。
 * 要反转哪一侧允许非严格不等式,把标有 (A) 的 < 改成 <=,并反转 (B) 处的循环。
 * 要求最小值,把 (B) 处的 < 改成 >。
 * 用法:
	int ind = ternSearch(0,n-1,[\&](int i){return a[i];});
 * 时间:O(\log(b-a))
 * 状态:已测试
 */
#pragma once

template <class F>
int ternSearch(int a, int b, F f) {
    assert(a <= b);
    while (b - a >= 5) {
        int mid = (a + b) / 2;
        if (f(mid) < f(mid + 1)) a = mid; // (A)
        else b = mid + 1;
    }
    for (int i = a + 1; i < b + 1; i++) {
        if (f(a) < f(i)) a = i; // (B)
    }
    return a;
}
