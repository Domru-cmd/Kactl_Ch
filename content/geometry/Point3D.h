/**
 * 作者:Ulf Lundstrom,灵感来自 tinyKACTL
 * 日期:2009-04-14
 * 许可:CC0
 * 来源:
 * 描述:三维空间中的点类。
 *  T 可以取 double 或 long long。
 * 用法:
 * 状态:已测试,但 phi 与 theta 除外
 */
#pragma once

template <class T>
struct Point3D {
    using P = Point3D;
    T x, y, z;

    explicit Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    bool operator<(P p) const {
        return tie(x, y, z) < tie(p.x, p.y, p.z);
    }
    bool operator==(P p) const {
        return tie(x, y, z) == tie(p.x, p.y, p.z);
    }
    P operator+(P p) const { return P(x + p.x, y + p.y, z + p.z); }
    P operator-(P p) const { return P(x - p.x, y - p.y, z - p.z); }
    P operator*(T d) const { return P(x * d, y * d, z * d); }
    P operator/(T d) const { return P(x / d, y / d, z / d); }
    T dot(P p) const { return x * p.x + y * p.y + z * p.z; }
    P cross(P p) const {
        return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    T dist2() const { return x * x + y * y + z * z; }
    double dist() const { return sqrt((double)dist2()); }
    // 到 x 轴的方位角(经度),范围 [-pi, pi]
    double phi() const { return atan2(y, x); }
    // 到 z 轴的极角(纬度),范围 [0, pi]
    double theta() const { return atan2(sqrt(x * x + y * y), z); }
    P unit() const { return *this / (T)dist(); } // 使 dist()=1
    // 返回垂直于 *this 与 p 的单位向量
    P normal(P p) const { return cross(p).unit(); }

    // 返回绕轴 axis 逆时针旋转 angle 弧度后的点
    P rotate(double angle, P axis) const {
        double s = sin(angle), c = cos(angle);
        P u = axis.unit();
        return u * dot(u) * (1 - c) + (*this) * c - cross(u) * s;
    }
};
