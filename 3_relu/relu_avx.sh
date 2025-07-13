g++ -O3 -mavx -std=c++11 relu_avx.cpp -o relu_avx.o || exit 1
sudo sysctl -w kernel.perf_event_paranoid=1
perf stat ./relu_avx.o 32