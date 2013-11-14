#!/bin/bash
#comparing write allocate vs. write no allocate
echo "Simulation 1: simulating 8KB, 2-way associative, split cache, block size = 128 bytes, write back, write no allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 2 -wb -nw spice.trace

echo "Simulation 1: simulating 8KB, 2-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 2 -wb -wa spice.trace

echo "Simulation 2: simulating 8KB, 2-way associative, split cache, block size = 128 bytes, write back, write no allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 2 -wb -nw cc.trace

echo "Simulation 2: simulating 8KB, 2-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 2 -wb -wa cc.trace

echo "Simulation 3: simulating 8KB, 2-way associative, split cache, block size = 128 bytes, write back, write no allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 2 -wb -nw tex.trace

echo "Simulation 3: simulating 8KB, 2-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 2 -wb -wa tex.trace

