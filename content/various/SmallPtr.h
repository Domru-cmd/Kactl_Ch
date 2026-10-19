/**
 * 作者:Simon Lindholm
 * 日期:2016-08-23
 * 许可:CC0
 * 来源:自己整理
 * 描述:指向 BumpAllocator 内存的 32 位指针。
 * 状态:已测试
 */
#pragma once

#include "BumpAllocator.h"

template <class T>
struct ptr {
    unsigned ind;

    ptr(T *p = 0) : ind(p ? unsigned((char *)p - buf) : 0) {
        assert(ind < sizeof buf);
    }
    T &operator*() const { return *(T *)(buf + ind); }
    T *operator->() const { return &**this; }
    T &operator[](int a) const { return (&**this)[a]; }
    explicit operator bool() const { return ind; }
};
