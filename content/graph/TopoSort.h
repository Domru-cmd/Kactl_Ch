/**
 * 作者:佚名
 * 日期:2002-09-13
 * 来源:早于 tinyKACTL
 * 描述:拓扑排序。输入为有向图。
 * 输出为顶点的排列,使所有边都从左指向右。
 * 若有环,返回列表的大小将小于 $n$ —— 从环可达的节点不会返回。
 * 时间:$O(|V|+|E|)$
 * 状态:已对拍
 */
#pragma once

vi topoSort(const vector<vi> &gr) {
    vi indeg((int)gr.size()), q;

    for (auto &li : gr) {
        for (int x : li) indeg[x]++;
    }
    for (int i = 0; i < (int)gr.size(); i++) {
        if (indeg[i] == 0) q.push_back(i);
    }
    for (int j = 0; j < (int)q.size(); j++) {
        for (int x : gr[q[j]]) {
            if (--indeg[x] == 0) q.push_back(x);
        }
    }

    return q;
}
