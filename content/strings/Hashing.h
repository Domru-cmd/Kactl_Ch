/**
 * 作者:Simon Lindholm
 * 日期:2015-03-15
 * 许可:CC0
 * 来源:自己整理
 * 描述:字符串哈希的若干直白方法。
 * 状态:已对拍
 */
#pragma once

// 模 2^64-1 的算术。比模 2^64 慢一倍且代码更多,
// 但可以对抗恶意数据(如 Thue-Morse 串:长度 2^10 的
// ABBA... 与 BAAB... 在模 2^64 下哈希相同)。
// 如果你认为数据随机,可改用 "typedef uint64_t H;";
// 或者如果不担心生日悖论,用模 10^9+7 也可以。
using ull = unsigned long long;
struct H {
    ull x;
    H(ull x = 0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) {
        auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64);
    }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3; // (阶约 3e9;随机也可以)

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
