#include<iostream>
#include<immintrin.h>

int main(int argc, char const *argv[])
{
    int N = std::stoi(argv[1]);
    size_t step = 8;

    float *A = static_cast<float*>(aligned_alloc(32, N*sizeof(float)));
    float *B = static_cast<float*>(aligned_alloc(32, N*sizeof(float)));



    for(size_t i = 0; i<N; i++) {
        A[i] = -30.0f + i;
    }

    for(size_t i = 0; i<N; i+=step) {
        __m256 x = _mm256_load_ps(A + i);          // 載入 8 個 float
        __m256 x2 = _mm256_mul_ps(x, x);               // x^2
        __m256 result = _mm256_sqrt_ps(x2);            // sqrt(x^2)
        _mm256_store_ps(B + i, result);           // 儲存結果
    }
    
    for(size_t i = 0; i<N; ++i){
        std::cout << B[i] << " ";
    }
    std::cout << '\n';

    return 0;
}
