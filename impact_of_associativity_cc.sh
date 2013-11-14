#!/bin/bash

echo "simulating 8KB, 1-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 1 -wb -wa cc.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 2 -wb -wa cc.trace

echo "simulating 8KB, 4-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 4 -wb -wa cc.trace

echo "simulating 8KB, 8-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 8 -wb -wa cc.trace

echo "simulating 8KB, 16-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 16 -wb -wa cc.trace

echo "simulating 8KB, 32-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 32 -wb -wa cc.trace

echo "simulating 8KB, 64-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 64 -wb -wa cc.trace