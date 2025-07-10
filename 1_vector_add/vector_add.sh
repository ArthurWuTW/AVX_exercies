g++ -std=c++11 vector_add.cpp -o vector_add.o
sudo sysctl -w kernel.perf_event_paranoid=1
perf stat ./vector_add.o 10241024
