/**
 * 作者:Lukas Polacek
 * 日期:2009-10-28
 * 许可:CC0
 * 来源:
 * 描述:简单的二分图匹配算法。图 $g$ 应为左侧部分的
 * 邻居表,$btoa$ 应为大小与右侧部分相同、初值全为
 * -1 的 vector。返回匹配的大小。$btoa[i]$ 为右侧顶点 $i$
 * 的匹配对象,未匹配时为 $-1$。
 * 时间:O(VE)
 * 用法:vi btoa(m, -1); dfsMatching(g, btoa);
 * 状态:可用
 */
#pragma once

bool find(int j, vector<vi> &g, vi &btoa, vi &vis) {
    if (btoa[j] == -1) return 1;
    vis[j] = 1;
    int di = btoa[j];
    for (int e : g[di]) {
        if (!vis[e] && find(e, g, btoa, vis)) {
            btoa[e] = di;
            return 1;
        }
    }
    return 0;
}
int dfsMatching(vector<vi> &g, vi &btoa) {
    vi vis;

    for (int i = 0; i < (int)g.size(); i++) {
        vis.assign((int)btoa.size(), 0);
        for (int j : g[i]) {
            if (find(j, g, btoa, vis)) {
                btoa[j] = i;
                break;
            }
        }
    }
    return (int)btoa.size() - (int)count(btoa.begin(), btoa.end(), -1);
}
