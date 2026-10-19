/**
 * 作者:Håkan Terelius
 * 日期:2009-08-26
 * 许可:CC0
 * 来源:http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * 描述:生成某个上限以内所有素数的筛法。isprime$[i]$ 为真当且仅当 $i$ 是素数。
 * 时间:lim=100'000'000 约 0.8 s。若只存奇数下标,快约 30\%。
 * 状态:已测试
 */
#pragma once

const int MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;

vi eratosthenesSieve(int lim) {
    isprime.set();
    isprime[0] = isprime[1] = 0;

    for (int i = 4; i < lim; i += 2) isprime[i] = 0;
    for (int i = 3; i * i < lim; i += 2) {
        if (isprime[i]) {
            for (int j = i * i; j < lim; j += i * 2) isprime[j] = 0;
        }
    }

    vi pr;
    for (int i = 2; i < lim; i++) {
        if (isprime[i]) pr.push_back(i);
    }

    return pr;
}
