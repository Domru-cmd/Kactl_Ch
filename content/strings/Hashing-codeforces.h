/**
 * 作者:Simon Lindholm
 * 日期:2015-03-15
 * 许可:CC0
 * 来源:自己整理
 * 描述:字符串哈希的若干直白方法。
 * 用于 Codeforces——它不支持 64 位,且题解可能被 hack。
 * 状态:已对拍
 */
#pragma once

using ull = unsigned long long;
static int C; // 在下面初始化

// 同时模两个素数与 2^32 的算术。
// 若 Thue-Morse 不适用,可改用 "typedef uint64_t H;"。
template <int M, class B>
struct A {
    int x;
    B b;

    A(int x = 0) : x(x), b(x) {}
    A(int x, B b) : x(x), b(b) {}
    A operator+(A o) {
        int y = x + o.x;
        return {y - (y >= M) * M, b + o.b};
    }
    A operator-(A o) {
        int y = x - o.x;
        return {y + (y < 0) * M, b - o.b};
    }
    A operator*(A o) { return {(int)(1LL * x * o.x % M), b * o.b}; }
    explicit operator ull() const { return x ^ (ull)b << 21; }
    bool operator==(A o) const { return (ull)*this == (ull)o; }
    bool operator<(A o) const { return (ull)*this < (ull)o; }
};
using H = A<1000000007, A<1000000009, unsigned>>;

struct HashInterval {
    vector<H> ha, pw;

    HashInterval(string &str) : ha((int)str.size() + 1), pw(ha) {
        pw[0] = 1;

        for (int i = 0; i < (int)str.size(); i++) {
            ha[i + 1] = ha[i] * C + str[i];
            pw[i + 1] = pw[i] * C;
        }
    }

    H hashInterval(int a, int b) { // 哈希 [a, b)
        return ha[b] - ha[a] * pw[b - a];
    }
};

vector<H> getHashes(string &str, int length) {
    if ((int)str.size() < length) return {};
    H h = 0, pw = 1;

    for (int i = 0; i < length; i++) {
        h = h * C + str[i];
        pw = pw * C;
    }
    vector<H> ret = {h};

    for (int i = length; i < (int)str.size(); i++) {
        ret.push_back(h = h * C + str[i] - pw * str[i - length]);
    }

    return ret;
}

H hashString(string &s) {
    H h{};

    for (char c : s) h = h * C + c;
    return h;
}

#include <sys/time.h>
int main() {
    timeval tp;
    gettimeofday(&tp, 0);
    C = (int)tp.tv_usec; // (小于模数)

    assert((ull)(H(1) * 2 + 1 - 3) == 0);
    // ...
}
