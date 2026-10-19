/**
 * 作者:Simon Lindholm
 * 日期:2016-07-23
 * 许可:CC0
 * 来源:自己整理
 * 描述:用于 STL 容器的 BumpAllocator。
 * 用法:vector<vector<int, small<int>>> ed(N);
 * 状态:已测试
 */
#pragma once

char buf[450 << 20] alignas(16);
size_t buf_ind = sizeof buf;

template <class T>
struct small {
    using value_type = T;

    small() {}
    template <class U>
    small(const U &) {}
    T *allocate(size_t n) {
        buf_ind -= n * sizeof(T);
        buf_ind &= 0 - alignof(T);
        return (T *)(buf + buf_ind);
    }
    void deallocate(T *, size_t) {}
};
