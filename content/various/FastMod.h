/**
 * 作者:Simon Lindholm
 * 日期:2020-05-30
 * 许可:CC0
 * 来源:https://en.wikipedia.org/wiki/Barrett_reduction
 * 描述:计算 $a \% b$ 比常规快约 5 倍,其中 $b$ 是常量但编译期未知。
 * 返回与 $a \pmod b$ 同余、且在 $[0, 2b)$ 内的值。
 * 状态:已证明正确,已对拍
 * 实测延迟低 4 倍、吞吐高 8 倍,见 stress-test。
 * 细节:
 * 更精确地说,可以证明:结果等于 0 当且仅当 $a = 0$,
 * 否则结果落在 $[1, (1 + a/2^64) * b)$ 内。
 */
#pragma once

using ull = unsigned long long;
struct FastMod {
    ull b, m;

    FastMod(ull b) : b(b), m(-1ULL / b) {}
    ull reduce(ull a) { // a % b + (0 或 b)
        return a - (ull)((__uint128_t(m) * a) >> 64) * b;
    }
};
