/**
 * 作者:Ulf Lundstrom
 * 日期:2009-04-07
 * 许可:CC0
 * 来源:自己的几何推理
 * 描述:返回半径为 radius 的球面上两点之间的最短距离——
 * 两点方位角(经度,自 x 轴起)为 f1 ($\phi_1$) 与 f2 ($\phi_2$),
 * 天顶角(纬度,自 z 轴起,0 = 北极)为 t1 ($\theta_1$) 与 t2 ($\theta_2$)。
 * 所有角度以弧度计。算法先把球坐标转换为直角坐标,
 * 因此若你已有直角坐标,可以只用最后两行。dx*radius 即两点在
 * x 方向的差,d*radius 即两点的总距离。
 * 状态:在 kattis:airlinehub 上测试
 */
#pragma once

double sphericalDistance(double f1, double t1,
        double f2, double t2, double radius) {
    double dx = sin(t2) * cos(f2) - sin(t1) * cos(f1);
    double dy = sin(t2) * sin(f2) - sin(t1) * sin(f1);
    double dz = cos(t2) - cos(t1);
    double d = sqrt(dx * dx + dy * dy + dz * dz);
    return radius * 2 * asin(d / 2);
}
