/**
 * 作者:Simon Lindholm
 * 日期:2016-09-06
 * 许可:CC0
 * 来源:自己整理
 * 描述:要从 SolveLinear 中恢复 $x$ 的所有唯一确定的值,做如下修改:
 * 状态:在 kattis:equationsolverplus 上测试,已对拍
 */
#pragma once

#include "SolveLinear.h"

for (int j = 0; j < n; j++) // 替代 for (int j = i + 1; j < n; j++)
    if (j != i)
// ... 然后末尾改为:
x.assign(m, undefined);
for (int i = 0; i < rank; i++) {
    for (int j = rank; j < m; j++) {
        if (fabs(A[i][j]) > eps) goto fail;
    }
    x[col[i]] = b[i] / A[i][i];
fail:;
}
