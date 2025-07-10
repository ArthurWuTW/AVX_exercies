#!/bin/bash
# 用法說明
if [ $# -lt 1 ]; then
    echo "Usage: $0 <program>"
    exit 1
fi

rm -r 

PROGRAM="./$1"  # 你的程式名稱
RUNS=24

echo "Running $PROGRAM $RUNS times with perf stat..."

# 建立暫存資料夾與清單檔案
OUT_DIR="perf_output"
rm -r "$OUT_DIR"
mkdir -p "$OUT_DIR"
SUMMARY_FILE="$OUT_DIR/$1.csv"

# 寫入表頭
echo "N,Time(ms),Cycles,Instructions,Branches,Branch-misses" > "$SUMMARY_FILE"

for i in $(seq 1 $RUNS); do
    echo "Run #$i"
    N=$((32 * (2**i)))

    perf stat -e task-clock,cycles,instructions,branches,branch-misses \
        -x, --log-fd 1 $PROGRAM $N > "$OUT_DIR/run_$i.txt"


    # 解析 perf 輸出
    TIME=$(grep "task-clock" "$OUT_DIR/run_$i.txt" | awk -F, '{print $1}' | tr -d ' ')
    CYCLES=$(grep "cpu_core/cycles" "$OUT_DIR/run_$i.txt" | awk -F, '{print $1}' | tr -d ' ')
    INSTR=$(grep "cpu_core/instructions" "$OUT_DIR/run_$i.txt" | awk -F, '{print $1}' | tr -d ' ')
    BRANCHES=$(grep "cpu_core/branches" "$OUT_DIR/run_$i.txt" | awk -F, '{print $1}' | tr -d ' ')
    BMISSES=$(grep "cpu_core/branch-misses" "$OUT_DIR/run_$i.txt" | awk -F, '{print $1}' | tr -d ' ')

    echo "$N,$TIME,$CYCLES,$INSTR,$BRANCHES,$BMISSES" >> "$SUMMARY_FILE"
done

echo "Done. Summary written to $SUMMARY_FILE"
cp $SUMMARY_FILE ./