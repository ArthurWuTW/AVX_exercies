#include <iostream>
#include <cstdlib>   // for aligned_alloc
#include <iomanip>   // for std::setprecision
#include <vector>

int main(int argc, char const *argv[])
{
    int N = std::stoi(argv[1]);

     std::vector<float> A(N), B(N), C(N);

    // 初始化 A, B
    for (int i = 0; i < N; ++i) {
        A[i] = i + 1.0f;
        B[i] = 0.5f;
    }

    // scalar 版本：逐一相乘
    for (int i = 0; i < N; ++i) {
        C[i] = A[i] * B[i];
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
    
    return 0;
}
