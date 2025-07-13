#include<iostream>
#include<immintrin.h>

int main(int argc, char const *argv[])
{
    int N = std::stoi(argv[1]);
    int step = 8;

    float *A = static_cast<float*>(aligned_alloc(32, N*sizeof(float) ));
    float *B = static_cast<float*>(aligned_alloc(32, N*sizeof(float) ));

    for(size_t i = 0; i<N; ++i){
        A[i] = -1.0f + i;
    }


    // Relu(n) = max(0, n)
    for(size_t i = 0; i<N; i+=step) {
        __m256 a = _mm256_load_ps(A + i);
        __m256 zero = _mm256_setzero_ps();
        __m256 b = _mm256_max_ps(a, zero);

        _mm256_store_ps(B + i, b);
    }

    for(size_t i = 0; i<N; ++i){
        std::cout << B[i] << " ";
    }
    std::cout << '\n';


    return 0;
}
