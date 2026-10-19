/**
 * 作者:Stanford
 * 日期:未知
 * 来源:Stanford Notebook
 * 描述:KD 树(二维,可扩展到三维)
 * 状态:在 excellentengineers 上测试
 */
#pragma once

#include "Point.h"

using T = long long;
using P = Point<T>;
const T INF = numeric_limits<T>::max();

bool on_x(P a, P b) { return a.x < b.x; }
bool on_y(P a, P b) { return a.y < b.y; }

struct Node {
    P pt; // 若是叶子,为其包含的唯一点
    T x0 = INF, x1 = -INF, y0 = INF, y1 = -INF; // 边界
    Node *first = 0, *second = 0;

    T distance(P p) { // 到某点的最小距离平方
        T x = (p.x < x0 ? x0 : p.x > x1 ? x1 : p.x);
        T y = (p.y < y0 ? y0 : p.y > y1 ? y1 : p.y);
        return (P(x, y) - p).dist2();
    }

    Node(vector<P> &&vp) : pt(vp[0]) {
        for (P p : vp) {
            x0 = min(x0, p.x);
            x1 = max(x1, p.x);
            y0 = min(y0, p.y);
            y1 = max(y1, p.y);
        }
        if (vp.size() > 1) {
            // 若宽 >= 高则按 x 划分(并不理想……)
            sort(vp.begin(), vp.end(), x1 - x0 >= y1 - y0 ? on_x : on_y);
            // 每棵子树取一半数组(中点有大量重复时性能不佳)
            int half = (int)vp.size() / 2;
            first = new Node({vp.begin(), vp.begin() + half});
            second = new Node({vp.begin() + half, vp.end()});
        }
    }
};

struct KDTree {
    Node *root;

    KDTree(const vector<P> &vp) : root(new Node({vp.begin(), vp.end()})) {}

    pair<T, P> search(Node *node, P p) {
        if (!node->first) {
            // 若不希望找到点自身,取消下面一行的注释:
            // if (p == node->pt) return {INF, P()};
            return make_pair((p - node->pt).dist2(), node->pt);
        }

        Node *f = node->first, *s = node->second;
        T bfirst = f->distance(p), bsec = s->distance(p);
        if (bfirst > bsec) {
            swap(bsec, bfirst);
            swap(f, s);
        }

        // 先搜索较近的一侧,必要时搜索另一侧
        auto best = search(f, p);
        if (bsec < best.first)
            best = min(best, search(s, p));
        return best;
    }

    // 求到某点的最近点及其距离平方
    // (要求 Point 有任意定义的 operator<)
    pair<T, P> nearest(P p) {
        return search(root, p);
    }
};
