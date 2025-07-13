g++ -O3 -mavx -std=c++11 vector_mask_avx.cpp -o vector_mask_avx.o || exit 1
sudo sysctl -w kernel.perf_event_paranoid=1
perf stat ./vector_mask_avx.o 32