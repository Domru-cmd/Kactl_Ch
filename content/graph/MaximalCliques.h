/**
 * 作者:Simon Lindholm
 * 日期:2018-07-18
 * 许可:CC0
 * 来源:https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
 * 描述:对图中的所有极大团运行一次回调(输入为
 * 对称 bitset 矩阵;不允许自环)。回调收到表示该极大团
 * 的 bitset。
 * 时间:O(3^{n/3}),稀疏图快得多
 * 状态:已对拍
 */
#pragma once
/// 可能的优化:在最顶层
/// 递归中忽略 'cands',按度数递增的顺序遍历节点,
/// 度数随节点被移除而减小。
/// (考虑到已有 MaximumClique,基本不重要)

using B = bitset<128>;
template <class F>
void cliques(vector<B> &eds, F f, B P = ~B(), B X = {}, B R = {}) {
    if (!P.any()) {
        if (!X.any()) f(R);
        return;
    }
    auto q = (P | X)._Find_first();
    auto cands = P & ~eds[q];

    for (int i = 0; i < (int)eds.size(); i++) {
        if (cands[i]) {
            R[i] = 1;
            cliques(eds, f, P & eds[i], X & eds[i], R);
            R[i] = P[i] = 0;
            X[i] = 1;
        }
    }
}
