g++ -O3 -mavx -std=c++11 dot_product.cpp -o dot_product.o || exit 1
sudo sysctl -w kernel.perf_event_paranoid=1
perf stat ./dot_product.o 32