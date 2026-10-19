/**
 * 作者:Simon Lindholm
 * 日期:2018-07-06
 * 许可:CC0
 * 描述:排列 → 整数。(不保序。)
 * 整数 → 排列可以用查表。
 * 时间:O(n)
 */
#pragma once

int permToInt(vi &v) {
    int use = 0, i = 0, r = 0;

    for (int x : v) {
        r = r * ++i + __builtin_popcount(use & -(1 << x));
        use |= 1 << x; // (注意:是负号,不是取反!)
    }

    return r;
}
