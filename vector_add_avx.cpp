#include<iostream>
#include<vector>
#include<chrono>
#include<immintrin.h>
#include<mm_malloc.h>

int main(int argc, char const *argv[])
{

    int N = std::stoi(argv[1]);

    // const int N = 512 * 1024 * 1024;
    const size_t step = 8;  // 每次處理 8 個 float（256-bit）

    // 分配對齊記憶體
    float* A = static_cast<float*>(aligned_alloc(32, N * sizeof(float)));
    float* B = static_cast<float*>(aligned_alloc(32, N * sizeof(float)));
    float* C = static_cast<float*>(aligned_alloc(32, N * sizeof(float)));


    // 初始化
    for (size_t i = 0; i < N; ++i) {
        A[i] = i * 0.1f;
        B[i] = i * 0.2f;
    }

    // auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; i += step) {
        __m256 a = _mm256_load_ps(A + i);
        __m256 b = _mm256_load_ps(B + i);
        __m256 c = _mm256_add_ps(a, b);
        _mm256_store_ps(C + i, c);
    }
    // auto end = std::chrono::high_resolution_clock::now();
    // double duration = std::chrono::duration<double, std::milli>(end - start).count();

    // std::cout << "AVX vector add took: " << duration << "ms\n";

    // for (int i = 0; i < N; ++i) {
    //     std::cout << C[i] << " ";
    // }
    // std::cout << "\n";

    return 0;
}
