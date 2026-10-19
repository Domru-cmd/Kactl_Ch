/**
 * 作者:Bjorn Martinsson
 * 日期:2020-06-03
 * 许可:CC0
 * 来源:自己整理
 * 描述:返回最小的 $x > 0$ 使 $a^x = b \pmod m$,
 * 若不存在则返回 $-1$。modLog(a,1,m) 可用来
 * 计算 $a$ 的阶。
 * 时间:O(\sqrt m)
 * 状态:对所有 0 <= a,x < 500 和 0 < m < 500 已测试。
 *
 * 细节:本算法用大步小步(baby-step giant-step)方法
 * 找到 (i,j) 使 a^(n * i) = b * a^j (mod m),其中 n > sqrt(m)
 * 且 0 < i, j <= n。若 a 与 m 互素,则 a^j 有模逆元,
 * 这意味着 a^(i * n - j) = b (mod m)。
 *
 * 不过这个具体实现即使不假设 a 与 m 互素也能工作,
 * 想法如下:
 *
 * 设 p^x 是 m 的一个素因子。则有三种情况:
 *   1. b 被 p^x 整除
 *   2. b 只被某个 p^y 整除,0<y<x
 *   3. b 不被 p 整除
 * 关键之处在于:情况 2 中 modLog(a,b,m)(如果存在)
 * 不可能 > sqrt(m)(严格说,不可能 >= log2(m))。
 * 所以一旦检查完所有 <= sqrt(m) 的 a 的指数,
 * 就不可能处于情况 2。情况 2 是唯一棘手的情况。
 *
 * 因此,允许非互素输入的改动就是:检查所有 <= n 的 a 的指数,
 * 再用简单的 gcd(a^n,m) == gcd(b,m) 检查处理不棘手的情况。
 */
#pragma once

ll modLog(ll a, ll b, ll m) {
    ll n = (ll)sqrt(m) + 1, e = 1, f = 1, j = 1;
    unordered_map<ll, ll> A;

    while (j <= n && (e = f = e * a % m) != b % m) {
        A[e * b % m] = j++;
    }
    if (e == b % m) return j;
    if (__gcd(m, e) == __gcd(m, b)) {
        for (int i = 2; i < n + 2; i++) {
            if (A.count(e = e * f % m)) return n * i - A[e];
        }
    }

    return -1;
}
