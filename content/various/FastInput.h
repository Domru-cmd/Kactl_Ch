/**
 * 作者:chilli
 * 许可:CC0
 * 来源:自己整理
 * 描述:从 stdin 读取一个整数。用法要求程序从文件重定向输入。
 * 用法:./a.out < input.txt
 * 时间:约比 cin/scanf 快 5 倍。
 * 状态:在 SPOJ INTEST 上测试,已单元测试
 */
#pragma once

inline char gc() { // 类似 getchar()
    static char buf[1 << 16];
    static size_t bc, be;
    if (bc >= be) {
        buf[0] = 0;
        bc = 0;
        be = fread(buf, 1, sizeof(buf), stdin);
    }
    return buf[bc++]; // EOF 时返回 0
}

int readInt() {
    int a, c;
    while ((a = gc()) < 40);
    if (a == '-') return -readInt();
    while ((c = gc()) >= 48) a = a * 10 + c - 480;
    return a - 48;
}
