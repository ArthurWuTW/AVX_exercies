#include<iostream>
#include<immintrin.h>

float dot_product_avx_N(const float* A, const float* B, int N) {
    __m256 acc = _mm256_setzero_ps();
    for (int i = 0; i < N; i += 8) {
        __m256 a = _mm256_load_ps(A + i);
        __m256 b = _mm256_load_ps(B + i);
        acc = _mm256_add_ps(acc, _mm256_mul_ps(a, b));
    }

    // 合併 256-bit
    __m128 low = _mm256_castps256_ps128(acc);
    __m128 high = _mm256_extractf128_ps(acc, 1);
    __m128 sum = _mm_add_ps(low, high);

    // 水平加總 4 個 float
    sum = _mm_hadd_ps(sum, sum);
    sum = _mm_hadd_ps(sum, sum);

    return _mm_cvtss_f32(sum);
}


int main(int argc, char const *argv[])
{
    int N = std::stoi(argv[1]);
    size_t step = 8;

    float *A = static_cast<float*>(aligned_alloc(32, N*sizeof(float)));
    float *B = static_cast<float*>(aligned_alloc(32, N*sizeof(float)));



    for(size_t i = 0; i<N; i++) {
        A[i] = i;
        B[i] = i;
    }

    float sum = dot_product_avx_N(A, B, N);
    
    std::cout << sum << " ";

    std::cout << '\n';

    return 0;
}
