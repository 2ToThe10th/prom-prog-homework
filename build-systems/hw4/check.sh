#!/bin/bash
set -e

mkdir -p bin
cd bin
cmake ..
make -j4
INPUT="example.jpg"
cp ../example.jpg ../map.png .
START=`date +%s%N`
./hw4_without_code_generation <<< $INPUT
END=`date +%s%N`
echo "Execution for hw4_without_code_generation time was "`expr $END - $START` nanoseconds.
START=`date +%s%N`
./hw4_with_code_generation <<< $INPUT
END=`date +%s%N`
echo "Execution for hw4_with_code_generation time was    "`expr $END - $START` nanoseconds.
diff filtered_with_code_generation_example.jpg filtered_without_code_generation_example.jpg
