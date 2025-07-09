# compile all
./vector_add_avx.sh || exit 1
./vector_add.sh || exit 1

./run_perf_range.sh vector_add_avx.o || exit 1
./run_perf_range.sh vector_add.o || exit 1
 
gnuplot plot_time_vs_size.gnu || exit 1

