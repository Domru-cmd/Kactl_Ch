/**
 * 作者:Simon Lindholm
 * 日期:2015-03-18
 * 许可:CC0
 * 来源:https://software.intel.com/sites/landingpage/IntrinsicsGuide/
 * 描述:SSE/AVX 内联函数的速查表,用于同时对多个数做运算。
 * 可带来约 4 倍的常数级提升,与循环展开正交。
 * 操作遵循模式 \texttt{"\_mm(256)?\_name\_(si(128|256)|epi(8|16|32|64)|pd|ps)"}。这里未全部列出;
 * 更多内容可对 \texttt{\_mm\_} 检索 \texttt{/usr/lib/gcc/{*}/4.9/include/}。
 * 若不支持 AVX,可尝试 128 位操作、"emmintrin.h",并在包含前 \#define \texttt{\_\_SSE\_\_} 与 \texttt{\_\_MMX\_\_}。
 * 对齐内存请用 \texttt{\_mm\_malloc(size, 32)} 或 \texttt{int buf[N] alignas(32)},但更推荐 loadu/storeu。
 */
#pragma once

#pragma GCC target ("avx2") // 或 sse4.1
#include "immintrin.h" /** keep-include */

using mi = __m256i;
#define L(x) _mm256_loadu_si256((mi*)&(x))

// 高层/专用方法:
// load(u)?_si256, store(u)?_si256, setzero_si256, _mm_malloc
// blendv_(epi8|ps|pd) (z?y:x), movemask_epi8 (hibits of bytes)
// i32gather_epi32(addr, x, 4): map addr[] over 32-b parts of x
// sad_epu8: sum of absolute differences of u8, outputs 4xi64
// maddubs_epi16: dot product of unsigned i7's, outputs 16xi15
// madd_epi16: dot product of signed i16's, outputs 8xi32
// extractf128_si256(, i) (256->128), cvtsi128_si32 (128->lo32)
// permute2f128_si256(x,x,1) swaps 128-bit lanes
// shuffle_epi32(x, 3*64+2*16+1*4+0) == x for each lane
// shuffle_epi8(x, y) takes a vector instead of an imm

// 适用于大多数数据类型的方法(如后缀 _epi32):
// set1, blend (i8?x:y), add, adds (sat.), mullo, sub, and/or,
// andnot, abs, min, max, sign(1,x), cmp(gt|eq), unpack(lo|hi)

int sumi32(mi m) {
    union {int v[8]; mi m;} u;
    u.m = m;
    int ret = 0;
    for (int i = 0; i < 8; i++) ret += u.v[i];
    return ret;
}
mi zero() { return _mm256_setzero_si256(); }
mi one() { return _mm256_set1_epi32(-1); }
bool all_zero(mi m) { return _mm256_testz_si256(m, m); }
bool all_one(mi m) { return _mm256_testc_si256(m, one()); }

ll example_filteredDotProduct(int n, short *a, short *b) {
    int i = 0;
    ll r = 0;
    mi zero = _mm256_setzero_si256(), acc = zero;

    while (i + 16 <= n) {
        mi va = L(a[i]), vb = L(b[i]);
        i += 16;
        va = _mm256_and_si256(_mm256_cmpgt_epi16(vb, va), va);
        mi vp = _mm256_madd_epi16(va, vb);
        acc = _mm256_add_epi64(_mm256_unpacklo_epi32(vp, zero),
            _mm256_add_epi64(acc, _mm256_unpackhi_epi32(vp, zero)));
    }
    union {ll v[4]; mi m;} u;
    u.m = acc;
    for (int i = 0; i < 4; i++) r += u.v[i];
    for (; i < n; i++) {
        if (a[i] < b[i]) r += a[i] * b[i]; // <- 等价
    }

    return r;
}
