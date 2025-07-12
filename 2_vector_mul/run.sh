# compile all
./vector_mul_avx.sh || exit 1
./vector_mul.sh || exit 1

./run_perf_range.sh vector_mul_avx.o || exit 1
./run_perf_range.sh vector_mul.o || exit 1
 
gnuplot plot_time_vs_size.gnu || exit 1

