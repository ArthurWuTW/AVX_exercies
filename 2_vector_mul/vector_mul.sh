g++ -O3 -mavx -std=c++11 vector_mul.cpp -o vector_mul.o || exit 1
sudo sysctl -w kernel.perf_event_paranoid=1
perf stat ./vector_mul.o 1000000