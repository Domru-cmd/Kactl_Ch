/**
 * 作者:chilli, SJTU, pajenegod
 * 日期:2020-03-04
 * 许可:CC0
 * 来源:自己整理
 * 描述:Pollard-rho 随机化因数分解算法。返回
 * 一个数的质因子,顺序任意(如 2299 -> \{11, 19, 11\})。
 * 时间:O(n^{1/4}),含小因子的数更快。
 * 状态:已对拍
 *
 * 细节:本实现采用了这里描述的改进
 * (https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Variants):
 * 按某个系数(此处经穷举测试取 40)累积 gcd 调用。
 * 依输入与 gcd 速度不同,性能约提升 6-10 倍。基准见:
 * (https://ideone.com/nGGD9T)
 *
 * 用 Binary GCD 可以把 GCD 提速约 1.75 倍
 * (https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/)。
 * 但累积 gcd 之后,瓶颈已从 gcd 调用转移到 modmul。
 * 由于 GCD 只占运行时间的约 12%,加速它意义不大。
 *
 * 若使用更快的模乘(比如 128 位整数上的 Montgomery 归约),这段代码大概还能更快。
 * 或者用二次筛法获得渐进改进——实际中约在 1e13 开始更快。
 *
 * 测试过 Brent 判圈算法,但没有显著减少 modmul 调用。
 *
 * 实现细节:
 * - prd 初值取 2 是为了处理 n = 4 的情形;对其它 n 无害,
 *   因为可以保证 n > 2。(Pollard rho 对素数幂一般会有问题,
 *   但所有更大的素数幂恰好都能正常工作。)
 * - t 初值取 30 是为了让第一次 gcd 检查更早发生,
 *   作为小数上的优化。
 * - 每次重启都会变换 f:因为判圈算法找到的不是环的第一个元素,
 *   而是距起点 k*|cycle| 的元素;若所有质因子对应的环长都相同,
 *   就会持续失败。例如取 f(x) = x^2 + 1 时,
 *   n = 352523 * 352817 会无限循环(所有环长均为 821)。
 * - 我们在 [i, n + i) 的剩余类上运算,modmul 本不为此设计,
 *   但 i 足够小时 modmul(x, x) 仍然正确。(参考 modmul-proof.tex 的证明:
 *   "S 在 [-c, 2c) 内"的论证不变,而由 S < 2c 与 S = x^2 (mod c)
 *   可推出 S < c + i^2,从而仍有 S < 2^63。)
 */
#pragma once

#include "ModMulLL.h"
#include "MillerRabin.h"

ull pollard(ull n) {
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    auto f = [&](ull x) { return modmul(x, x, n) + i; };

    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) {
            x = ++i;
            y = f(x);
        }
        if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
        x = f(x);
        y = f(f(y));
    }

    return __gcd(prd, n);
}

vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    ull x = pollard(n);
    auto l = factor(x);
    auto r = factor(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
}
