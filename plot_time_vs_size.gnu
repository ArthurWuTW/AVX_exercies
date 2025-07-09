set datafile separator ","

set terminal pngcairo size 1000,600 enhanced font 'Verdana,10'
set output 'time_scalar_vs_avx.png'

set title "Scalar vs AVX Performance"
set xlabel "Vector Size (N)"
set ylabel "Time (ms)"
set key top left
set grid

set logscale x 2
set xtics format "10^{%L}"

# 畫兩條線：過濾掉含 <notcounted> 的行
plot \
    '< grep -v "<notcounted>" vector_add.o.csv'      using 1:2 with linespoints lt rgb "red"   pointtype 7 lw 2 title "Scalar", \
    '< grep -v "<notcounted>" vector_add_avx.o.csv'  using 1:2 with linespoints lt rgb "blue"  pointtype 7 lw 2 title "AVX"