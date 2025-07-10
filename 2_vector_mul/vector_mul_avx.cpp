#include <immintrin.h>
#include <iostream>
#include <cstdlib>   // for aligned_alloc
#include <iomanip>   // for std::setprecision

int main() {
    const int N = 8;  // 一次處理 8 個 float
    float* A = static_cast<float*>(aligned_alloc(32, N * sizeof(float)));
    float* B = static_cast<float*>(aligned_alloc(32, N * sizeof(float)));
    float* C = static_cast<float*>(aligned_alloc(32, N * sizeof(float)));

    // 初始化 A, B
    for (int i = 0; i < N; ++i) {
        A[i] = i + 1.0f;   // A = [1.0, 2.0, ..., 8.0]
        B[i] = 2.0f;       // B = [2.0, 2.0, ..., 2.0]
    }

    // 載入向量，做乘法
    __m256 va = _mm256_load_ps(A);
    __m256 vb = _mm256_load_ps(B);
    __m256 vc = _mm256_mul_ps(va, vb);  // C = A * B

    // 儲存結果
    _mm256_store_ps(C, vc);

    // 印出結果
    std::cout << "A * B = ";
    for (int i = 0; i < N; ++i) {
        std::cout << std::fixed << std::setprecision(1) << C[i] << " ";
    }
    std::cout << "\n";

    // 釋放記憶體
    free(A);
    free(B);
    free(C);

    return 0;
}