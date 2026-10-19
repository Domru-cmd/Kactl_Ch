/**
 * 作者:Simon Lindholm
 * 日期:2016-12-09
 * 许可:CC0
 * 来源:http://www.mimuw.edu.pl/~mucha/pub/mucha_sankowski_focs04.pdf
 * 描述:一般图的匹配。
 * 以 $N / mod$ 的概率失败。
 * 时间:O(N^3)
 * 状态:测试不充分
 */
#pragma once

#include "../numerical/MatrixInverse-mod.h"

vector<pii> generalMatching(int N, vector<pii> &ed) {
    vector<vector<ll>> mat(N, vector<ll>(N)), A;

    for (pii pa : ed) {
        int a = pa.first, b = pa.second, r = rand() % mod;
        mat[a][b] = r;
        mat[b][a] = (mod - r) % mod;
    }

    int r = matInv(A = mat), M = 2 * N - r, fi, fj;
    assert(r % 2 == 0);

    if (M != N) {
        do {
            mat.resize(M, vector<ll>(M));
            for (int i = 0; i < N; i++) {
                mat[i].resize(M);
                for (int j = N; j < M; j++) {
                    int r = rand() % mod;
                    mat[i][j] = r;
                    mat[j][i] = (mod - r) % mod;
                }
            }
        } while (matInv(A = mat) != M);
    }

    vi has(M, 1);
    vector<pii> ret;

    for (int it = 0; it < M / 2; it++) {
        for (int i = 0; i < M; i++) {
            if (has[i]) {
                for (int j = i + 1; j < M; j++) {
                    if (A[i][j] && mat[i][j]) {
                        fi = i;
                        fj = j;
                        goto done;
                    }
                }
            }
        }
        assert(0);
done:
        if (fj < N) ret.emplace_back(fi, fj);
        has[fi] = has[fj] = 0;

        for (int sw = 0; sw < 2; sw++) {
            ll a = modpow(A[fi][fj], mod - 2);
            for (int i = 0; i < M; i++) {
                if (has[i] && A[i][fj]) {
                    ll b = A[i][fj] * a % mod;
                    for (int j = 0; j < M; j++) {
                        A[i][j] = (A[i][j] - A[fi][j] * b) % mod;
                    }
                }
            }
            swap(fi, fj);
        }
    }

    return ret;
}
