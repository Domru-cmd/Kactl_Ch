/**
 * 作者:Simon Lindholm
 * 许可:CC0
 * 来源:http://codeforces.com/blog/entry/8219
 * 描述:区间 DP 时:$a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$,其中(最小的)最优 $k$ 随 $i$ 与 $j$ 递增,
 *  则可以按区间长度递增的顺序求解,并把 $a[i][j]$ 的 $k = p[i][j]$ 的搜索范围限制在 $p[i][j-1]$ 与 $p[i+1][j]$ 之间。
 *  这就是 Knuth DP。充分条件是:对所有 $a \le b \le c \le d$ 有 $f(b,c) \le f(a,d)$ 且 $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$。
 *  另可参见:LineContainer(数据结构章)、单调队列、三分搜索。
 * 时间:O(N^2)
 */
