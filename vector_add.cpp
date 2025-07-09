#include<iostream>
#include<vector>
#include<chrono>

int main(int argc, char const *argv[])
{
    size_t N = std::stoi(argv[1]);
    // const int N = 512 * 1024 * 1024;
    std::vector<float> A(N), B(N), C(N);

    // init
    for (size_t i = 0; i < N; i++) {
        A[i] = i * 0.1f;
        B[i] = i * 0.2f;
    }

    // auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }
    // auto end = std::chrono::high_resolution_clock::now();
    // double duration = std::chrono::duration<double, std::milli>(end - start).count();
    
    // for (size_t i = 0; i < N; i++) {
    //     std::cout << C[i] << " ";
    // }
    // std::cout << "Scalar vector add took: " << duration << "ms \n";

    return 0;
}
