#include<iostream>
#include<immintrin.h>

int main(int argc, char const *argv[])
{
    int N = std::stoi(argv[1]);
    size_t step = 8;

    float *A = static_cast<float*>(aligned_alloc(32, N*sizeof(float)));
    float *B = static_cast<float*>(aligned_alloc(32, N*sizeof(float)));
    float *M = static_cast<float*>(aligned_alloc(32, N*sizeof(float)));



    for(size_t i = 0; i<N; i++) {
        A[i] = 30.0f + i;
    }

    // You are given an array of temperature readings (float array), but some of the values are abnormally high (i.e., above 40°C). 
    // Using AVX intrinsics, perform the following:
    // Clamp all temperature values greater than 40°C to exactly 40.0°C
    // Leave all other values unchanged

    for(size_t i = 0; i<N; i+=step) {
        __m256 limit = _mm256_set1_ps(40.0f);
        __m256 a = _mm256_load_ps(A + i);
        __m256 mask = _mm256_cmp_ps(a, limit, _CMP_GT_OQ);
        _mm256_store_ps(M + i, mask);
        __m256 corrected = _mm256_blendv_ps(a, limit, mask);
        _mm256_store_ps(B + i, corrected);
    }
    
    for(size_t i = 0; i<N; ++i){
        std::cout << B[i] << " ";
    }
    std::cout << '\n';

    std::cout << "MASK: " << '\n';
    for(size_t i = 0; i<N; ++i){
        std::cout << M[i] << " ";
    }
    std::cout << '\n';

    return 0;
}
