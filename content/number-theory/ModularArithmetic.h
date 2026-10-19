/**
 * 作者:Lukas Polacek, Joshua Andersson
 * 日期:2009-09-28
 * 许可:CC0
 * 来源:民间流传
 * 描述:模运算的运算符重载。需要先把 {\tt mod} 设为
 * 某个数,然后即可使用该结构体。
 */
#pragma once

#include "euclid.h"

const ll mod = 17; // 改成其它数
struct Mod {
    ll x;

    Mod(ll y) : Mod(y % mod + mod, 0) {}
    Mod(ll y, int) : x(y < mod ? y : y - mod) {}

    Mod operator+(Mod b) { return {x + b.x, 0}; }
    Mod operator-(Mod b) { return {x - b.x + mod, 0}; }
    Mod operator*(Mod b) { return {x * b.x % mod, 0}; }
    Mod operator/(Mod b) { return *this * invert(b); }

    Mod invert(Mod a) {
        ll x, y, g = euclid(a.x, mod, x, y);
        assert(g == 1);
        return x;
    }

    Mod operator^(ll e) {
        if (!e) return 1;
        Mod r = *this ^ (e / 2);
        r = r * r;
        return e & 1 ? *this * r : r;
    }
};
