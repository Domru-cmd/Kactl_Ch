/**
 * 作者:Simon Lindholm
 * 日期:2015-09-12
 * 许可:CC0
 * 来源:自己整理
 * 描述:需要动态分配很多对象且不在意释放时使用。
 * 否则 "new X" 的开销约为每次分配 0.05us + 16 字节。
 * 状态:已测试
 */
#pragma once

// 全局定义,或放在单个类里:
static char buf[450 << 20];
void *operator new(size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void *)&buf[i -= s];
}
void operator delete(void *) {}
