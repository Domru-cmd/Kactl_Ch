/**
 * 作者:chilli, SJTU, Janez Konc
 * 日期:2019-05-10
 * 许可:GPL3+
 * 来源:https://en.wikipedia.org/wiki/MaxCliqueDyn_maximum_clique_algorithm, https://gitlab.com/janezkonc/mcqd/blob/master/mcqd.h
 * 描述:快速求图的最大团(输入为对称 bitset
 * 矩阵;不允许自环)。可通过在补图上求团来
 * 得到最大独立集。
 * 时间:n=155 的最坏情形随机图(p=.90)约 1s。
 * 稀疏图更快。
 * 状态:已对拍
 */
using vb = vector<bitset<200>>;
struct Maxclique {
    double limit = 0.025, pk = 0;
    struct Vertex { int i, d = 0; };
    using vv = vector<Vertex>;
    vb e;
    vv V;
    vector<vi> C;
    vi qmax, q, S, old;

    void init(vv &r) {
        for (auto &v : r) v.d = 0;
        for (auto &v : r) {
            for (auto j : r) v.d += e[v.i][j.i];
        }
        sort(r.begin(), r.end(), [](auto a, auto b) { return a.d > b.d; });
        int mxD = r[0].d;
        for (int i = 0; i < (int)r.size(); i++) r[i].d = min(i, mxD) + 1;
    }

    void expand(vv &R, int lev = 1) {
        S[lev] += S[lev - 1] - old[lev];
        old[lev] = S[lev - 1];

        while ((int)R.size()) {
            if ((int)q.size() + R.back().d <= (int)qmax.size()) return;
            q.push_back(R.back().i);
            vv T;

            for (auto v : R) {
                if (e[R.back().i][v.i]) T.push_back({v.i});
            }
            if ((int)T.size()) {
                if (S[lev]++ / ++pk < limit) init(T);
                int j = 0, mxk = 1, mnk = max((int)qmax.size() - (int)q.size() + 1, 1);
                C[1].clear();
                C[2].clear();

                for (auto v : T) {
                    int k = 1;
                    auto f = [&](int i) { return e[v.i][i]; };
                    while (any_of(C[k].begin(), C[k].end(), f)) k++;
                    if (k > mxk) {
                        mxk = k;
                        C[mxk + 1].clear();
                    }
                    if (k < mnk) T[j++].i = v.i;
                    C[k].push_back(v.i);
                }
                if (j > 0) T[j - 1].d = 0;
                for (int k = mnk; k < mxk + 1; k++) {
                    for (int i : C[k]) {
                        T[j].i = i;
                        T[j++].d = k;
                    }
                }
                expand(T, lev + 1);
            }
            else if ((int)q.size() > (int)qmax.size()) qmax = q;
            q.pop_back();
            R.pop_back();
        }
    }

    vi maxClique() {
        init(V);
        expand(V);
        return qmax;
    }

    Maxclique(vb conn) : e(conn), C((int)e.size() + 1), S((int)C.size()), old(S) {
        for (int i = 0; i < (int)e.size(); i++) V.push_back({i});
    }
};
