g++ -O3 -mavx -std=c++11 vector_add_avx.cpp -o vector_add_avx.o
sudo sysctl -w kernel.perf_event_paranoid=1
perf stat ./vector_add_avx.o 10241024
