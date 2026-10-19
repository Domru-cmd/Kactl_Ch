/**
 * 作者:Simon Lindholm
 * 日期:2016-10-08
 * 许可:CC0
 * 来源:自己整理
 * 描述:支持大区间加/赋值并计算区间最大值的线段树(push 式动态开点)。
 * 可以改成其它运算。
 * 配合 bump allocator 使用性能更好;用 SmallPtr 或隐式下标可节省内存。
 * 时间:O(\log N)。
 * 用法:Node* tr = new Node(v, 0, sz(v));
 * 状态:部分对拍验证
 */
#pragma once

#include "../various/BumpAllocator.h"

const int inf = 1e9;
struct Node {
    Node *l = 0, *r = 0;
    int lo, hi, mset = inf, madd = 0, val = -inf;

    Node(int lo, int hi) : lo(lo), hi(hi) {} // 一大段 -inf 区间
    Node(vi &v, int lo, int hi) : lo(lo), hi(hi) {
        if (lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid);
            r = new Node(v, mid, hi);
            val = max(l->val, r->val);
        } else val = v[lo];
    }

    int query(int L, int R) {
        if (R <= lo || hi <= L) return -inf;
        if (L <= lo && hi <= R) return val;
        push();
        return max(l->query(L, R), r->query(L, R));
    }

    void set(int L, int R, int x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            mset = val = x;
            madd = 0;
        } else {
            push();
            l->set(L, R, x);
            r->set(L, R, x);
            val = max(l->val, r->val);
        }
    }

    void add(int L, int R, int x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            if (mset != inf) mset += x;
            else madd += x;
            val += x;
        } else {
            push();
            l->add(L, R, x);
            r->add(L, R, x);
            val = max(l->val, r->val);
        }
    }

    void push() {
        if (!l) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
        }
        if (mset != inf) {
            l->set(lo, hi, mset);
            r->set(lo, hi, mset);
            mset = inf;
        } else if (madd) {
            l->add(lo, hi, madd);
            r->add(lo, hi, madd);
            madd = 0;
        }
    }
};
