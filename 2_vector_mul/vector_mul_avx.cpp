#include <immintrin.h>
#include <iostream>
#include <cstdlib>   // for aligned_alloc
#include <iomanip>   // for std::setprecision

int main(int argc, char const *argv[])
{

    int N = std::stoi(argv[1]);
    const size_t step = 8;  // 每次處理 8 個 float（256-bit）

    
    float* A = static_cast<float*>(aligned_alloc(32, N * sizeof(float)));
    float* B = static_cast<float*>(aligned_alloc(32, N * sizeof(float)));
    float* C = static_cast<float*>(aligned_alloc(32, N * sizeof(float)));

    // 初始化 A, B
    for (int i = 0; i < N; ++i) {
        A[i] = i + 1.0f;   // A = [1.0, 2.0, ..., 8.0]
        B[i] = 0.5f;       // B = [2.0, 2.0, ..., 2.0]
    }

    for (size_t i = 0; i < N; i += step) {
        __m256 a = _mm256_load_ps(A + i);
        __m256 b = _mm256_load_ps(B + i);
        __m256 c = _mm256_mul_ps(a, b);
        _mm256_store_ps(C + i, c);
    }

    // 印出結果
    // std::cout << "A * B = ";
    // for (int i = 0; i < N; ++i) {
    //     std::cout << std::fixed << std::setprecision(1) << C[i] << " ";
    // }
    // std::cout << "\n";

    // Fake use for preventing from dead store elimination
    float acc = C[0];
    std::cout << acc << '\n';

    // 釋放記憶體
    free(A);
    free(B);
    free(C);

    return 0;
}