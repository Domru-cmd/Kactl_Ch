/**
 * 作者:Codeforces 上的网友
 * 日期:2017-03-14
 * 来源:民间流传
 * 描述:一种简短的自平衡树。可作为支持对数时间
 *  分裂/合并的顺序容器,且易于附加额外数据。
 * 时间:O(\log N)
 * 状态:已对拍
 */
#pragma once

struct Node {
    Node *l = 0, *r = 0;
    int val, y, c = 1;

    Node(int val) : val(val), y(rand()) {}
    void recalc();
};

int cnt(Node *n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }

template <class F>
void each(Node *n, F f) {
    if (n) {
        each(n->l, f);
        f(n->val);
        each(n->r, f);
    }
}

pair<Node *, Node *> split(Node *n, int k) {
    if (!n) return {};
    if (cnt(n->l) >= k) { // 若要实现 lower_bound(k),改成 "n->val >= k"
        auto [L, R] = split(n->l, k);
        n->l = R;
        n->recalc();
        return {L, n};
    } else {
        auto [L, R] = split(n->r, k - cnt(n->l) - 1); // 或者直接用 "k"
        n->r = L;
        n->recalc();
        return {n, R};
    }
}

Node *merge(Node *l, Node *r) {
    if (!l) return r;
    if (!r) return l;
    if (l->y > r->y) {
        l->r = merge(l->r, r);
        l->recalc();
        return l;
    } else {
        r->l = merge(l, r->l);
        r->recalc();
        return r;
    }
}

Node *ins(Node *t, Node *n, int pos) {
    auto [l, r] = split(t, pos);
    return merge(merge(l, n), r);
}

// 示例用法:把区间 [l, r) 移动到下标 k 处
void move(Node *&t, int l, int r, int k) {
    Node *a, *b, *c;

    tie(a, b) = split(t, l);
    tie(b, c) = split(b, r - l);
    if (k <= l) t = merge(ins(a, b, k), c);
    else t = merge(a, ins(c, b, k - r));
}
