/**
 * 作者:Simon Lindholm
 * 日期:2015-01-31
 * 许可:CC0
 * 来源:自己整理
 * 描述:用于给角度排序的类(以整点表示,并记录绕原点旋转的圈数)。
 *  适合旋转扫描。有时也用来表示点或向量。
 * 用法:
 *  vector<Angle> v = {w[0], w[0].t360() ...}; // 已排序
 *  int j = 0; rep(i,0,n) { while (v[j] < v[i].t180()) ++j; }
 *  // 扫动 j,使 (j-i) 表示以 0 和 i 为顶点的正向三角形个数
 * 状态:在用,工作良好
 */
#pragma once

struct Angle {
    int x, y;
    int t;

    Angle(int x, int y, int t = 0) : x(x), y(y), t(t) {}
    Angle operator-(Angle b) const { return {x - b.x, y - b.y, t}; }
    int half() const {
        assert(x || y);
        return y < 0 || (y == 0 && x < 0);
    }
    Angle t90() const { return {-y, x, t + (half() && x >= 0)}; }
    Angle t180() const { return {-x, -y, t + half()}; }
    Angle t360() const { return {x, y, t + 1}; }
};

bool operator<(Angle a, Angle b) {
    // 加上 a.dist2() 与 b.dist2() 也可比较距离
    return make_tuple(a.t, a.half(), a.y * (ll)b.x) <
           make_tuple(b.t, b.half(), a.x * (ll)b.y);
}

// 给定两个点,计算它们之间的最小角,
// 即覆盖所定义线段的角度。
pair<Angle, Angle> segmentAngles(Angle a, Angle b) {
    if (b < a) swap(a, b);
    return (b < a.t180() ?
            make_pair(a, b) : make_pair(b, a.t360()));
}

Angle operator+(Angle a, Angle b) { // 点 a + 向量 b
    Angle r(a.x + b.x, a.y + b.y, a.t);
    if (a.t180() < r) r.t--;
    return r.t180() < a ? r.t360() : r;
}

Angle angleDiff(Angle a, Angle b) { // 角度 b - 角度 a
    int tu = b.t - a.t;
    a.t = b.t;
    return {a.x * b.x + a.y * b.y, a.x * b.y - a.y * b.x, tu - (b < a)};
}
