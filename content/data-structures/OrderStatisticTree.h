/**
 * 作者:Simon Lindholm
 * 日期:2016-03-22
 * 许可:CC0
 * 来源:hacKIT, NWERC 2015
 * 描述:一个集合(非多重集!),支持查询第 n 小元素
 * 以及某元素的下标(排名)。
 * 想要 map 版本,请修改 \texttt{null\_type}。
 * 时间:O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

void example() {
    Tree<int> t, t2;
    t.insert(8);

    auto it = t.insert(10).first;
    assert(it == t.lower_bound(9));
    assert(t.order_of_key(10) == 1);
    assert(t.order_of_key(11) == 2);
    assert(*t.find_by_order(0) == 8);
    t.join(t2); // 前提是 T < T2 或 T > T2,把 t2 并入 t
}
