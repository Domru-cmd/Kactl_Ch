/**
 * 作者:Lukas Polacek
 * 日期:2009-10-30
 * 许可:CC0
 * 来源:民间流传 / TopCoder
 * 描述:计算前缀和 a[0] + a[1] + ... + a[pos - 1],支持单点修改
 * (按新旧值之差更新)。
 * 时间:两个操作都是 O(\log N)。
 * 状态:已对拍
 */
#pragma once

struct FT {
    vector<ll> s;

    FT(int n) : s(n) {}

    void update(int pos, ll dif) { // a[pos] += dif
        for (; pos < (int)s.size(); pos |= pos + 1) {
            s[pos] += dif;
        }
    }

    ll query(int pos) { // [0, pos) 的元素和
        ll res = 0;

        for (; pos > 0; pos &= pos - 1) {
            res += s[pos - 1];
        }

        return res;
    }

    int lower_bound(ll sum) { // 最小的 pos 使 [0, pos] 的元素和 >= sum
        // 若不存在这样的前缀和返回 n;若 sum <= 0 返回 -1
        if (sum <= 0) return -1;
        int pos = 0;

        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= (int)s.size() && s[pos + pw - 1] < sum) {
                pos += pw;
                sum -= s[pos - 1];
            }
        }

        return pos;
    }
};
