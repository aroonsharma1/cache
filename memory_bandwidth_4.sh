#!/bin/bash
#comparing write allocate vs. write no allocate
echo "Simulation 4: simulating 16KB, 4-way associative, split cache, block size = 64 bytes, write back, write no allocate
"
./sim -is 16384 -ds 16384 -bs 64 -a 4 -wb -nw spice.trace

echo "Simulation 4: simulating 16KB, 4-way associative, split cache, block size = 64 bytes, write back, write allocate
"
./sim -is 16384 -ds 16384 -bs 64 -a 4 -wb -wa spice.trace

echo "Simulation 5: simulating 16KB, 4-way associative, split cache, block size = 64 bytes, write back, write no allocate
"
./sim -is 16384 -ds 16384 -bs 64 -a 4 -wb -nw cc.trace

echo "Simulation 5: simulating 16KB, 4-way associative, split cache, block size = 64 bytes, write back, write allocate
"
./sim -is 16384 -ds 16384 -bs 64 -a 4 -wb -wa cc.trace

echo "Simulation 6: simulating 16KB, 4-way associative, split cache, block size = 64 bytes, write back, write no allocate
"
./sim -is 16384 -ds 16384 -bs 64 -a 4 -wb -nw tex.trace

echo "Simulation 6: simulating 16KB, 4-way associative, split cache, block size = 64 bytes, write back, write allocate
"
./sim -is 16384 -ds 16384 -bs 64 -a 4 -wb -wa tex.trace