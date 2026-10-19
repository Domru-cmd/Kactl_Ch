/**
 * 作者:Simon Lindholm
 * 日期:2016-07-25
 * 来源:https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/DataStructure/LinkCutTree.h
 * 描述:维护一片无根树(森林)。可以加边、删边(只要
 * 结果仍是森林),并查询两个节点是否在同一棵树中。
 * 时间:所有操作均摊 O(\log N)。
 * 状态:对 N <= 20 做过部分对拍
 */
#pragma once

struct Node { // Splay 树。根的 pp 指向其代表树中的父节点。
    Node *p = 0, *pp = 0, *c[2];
    bool flip = 0;

    Node() {
        c[0] = c[1] = 0;
        fix();
    }
    void fix() {
        if (c[0]) c[0]->p = this;
        if (c[1]) c[1]->p = this;
        // (如需维护子树和信息等,在此更新)
    }
    void pushFlip() {
        if (!flip) return;
        flip = 0;
        swap(c[0], c[1]);
        if (c[0]) c[0]->flip ^= 1;
        if (c[1]) c[1]->flip ^= 1;
    }
    int up() { return p ? p->c[1] == this : -1; }

    void rot(int i, int b) {
        int h = i ^ b;
        Node *x = c[i], *y = b == 2 ? x : x->c[h], *z = b ? y : x;
        if ((y->p = p)) p->c[up()] = y;
        c[i] = z->c[i ^ 1];
        if (b < 2) {
            x->c[h] = y->c[h ^ 1];
            y->c[h ^ 1] = x;
        }
        z->c[i ^ 1] = this;
        fix();
        x->fix();
        y->fix();
        if (p) p->fix();
        swap(pp, y->pp);
    }

    void splay() { /// 把 this 旋到根。结束时一定没有待翻转标记。
        for (pushFlip(); p;) {
            if (p->p) p->p->pushFlip();
            p->pushFlip();
            pushFlip();
            int c1 = up(), c2 = p->up();
            if (c2 == -1) p->rot(c1, 2);
            else p->p->rot(c2, c1 != c2);
        }
    }

    Node *first() { /// 返回以 this 为根的子树中的最小元素,并旋到顶端。
        pushFlip();
        return c[0] ? c[0]->first() : (splay(), this);
    }
};

struct LinkCut {
    vector<Node> node;

    LinkCut(int N) : node(N) {}

    void link(int u, int v) { // 添加边 (u, v)
        assert(!connected(u, v));
        makeRoot(&node[u]);
        node[u].pp = &node[v];
    }
    void cut(int u, int v) { // 删除边 (u, v)
        Node *x = &node[u], *top = &node[v];
        makeRoot(top);
        x->splay();
        assert(top == (x->pp ? x->pp : x->c[0]));
        if (x->pp) x->pp = 0;
        else {
            x->c[0] = top->p = 0;
            x->fix();
        }
    }
    bool connected(int u, int v) { // u、v 是否在同一棵树中?
        Node *nu = access(&node[u])->first();
        return nu == access(&node[v])->first();
    }
    void makeRoot(Node *u) { /// 把 u 移到其代表树的根。
        access(u);
        u->splay();
        if (u->c[0]) {
            u->c[0]->p = 0;
            u->c[0]->flip ^= 1;
            u->c[0]->pp = u;
            u->c[0] = 0;
            u->fix();
        }
    }
    Node *access(Node *u) { /// 把 u 移到所在辅助树的根。返回根辅助树的根。
        u->splay();
        while (Node *pp = u->pp) {
            pp->splay();
            u->pp = 0;
            if (pp->c[1]) {
                pp->c[1]->p = 0;
                pp->c[1]->pp = pp;
            }
            pp->c[1] = u;
            pp->fix();
            u = pp;
        }
        return u;
    }
};
