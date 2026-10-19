/**
 * 作者:Simon Lindholm
 * 日期:2016-07-24
 * 许可:CC0
 * 来源:民间流传
 * 描述:求 \{x, y, d\} 使 ax + by = d = gcd(a, b)。
 * 状态:已测试
 */

static BigInteger[] euclid(BigInteger a, BigInteger b) {
    BigInteger x = BigInteger.ONE, yy = x;
    BigInteger y = BigInteger.ZERO, xx = y;

    while (b.signum() != 0) {
        BigInteger q = a.divide(b), t = b;
        b = a.mod(b);
        a = t;
        t = xx;
        xx = x.subtract(q.multiply(xx));
        x = t;
        t = yy;
        yy = y.subtract(q.multiply(yy));
        y = t;
    }

    return new BigInteger[]{x, y, a};
}
