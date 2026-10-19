/**
 * 作者:Johan Sannemo, Simon Lindholm
 * 日期:2016-12-15
 * 许可:CC0
 * 描述:求二分图的最小点覆盖。
 *  大小与最大匹配相同,其补集为最大独立集。
 * 状态:已对拍
 */
#pragma once

#include "DFSMatching.h"

vi cover(vector<vi> &g, int n, int m) {
    vi match(m, -1);
    int res = dfsMatching(g, match);
    vector<bool> lfound(n, true), seen(m);

    for (int it : match) {
        if (it != -1) lfound[it] = false;
    }
    vi q, cover;
    for (int i = 0; i < n; i++) {
        if (lfound[i]) q.push_back(i);
    }
    while (!q.empty()) {
        int i = q.back();
        q.pop_back();
        lfound[i] = 1;
        for (int e : g[i]) {
            if (!seen[e] && match[e] != -1) {
                seen[e] = true;
                q.push_back(match[e]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!lfound[i]) cover.push_back(i);
    }
    for (int i = 0; i < m; i++) {
        if (seen[i]) cover.push_back(n + i);
    }
    assert((int)cover.size() == res);
    return cover;
}
