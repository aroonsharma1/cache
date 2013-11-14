#!/bin/bash
echo "simulating 8KB, 2-way associative, split cache, block size = 4 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 4 -a 2 -wb -wa tex.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 8 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 8 -a 2 -wb -wa tex.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 16 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 16 -a 2 -wb -wa tex.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 32 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 32 -a 2 -wb -wa tex.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 64 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 64 -a 2 -wb -wa tex.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 128 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 128 -a 2 -wb -wa tex.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 256 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 256 -a 2 -wb -wa tex.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 512 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 512 -a 2 -wb -wa tex.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 1024 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 1024 -a 2 -wb -wa tex.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 2048 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 2048 -a 2 -wb -wa tex.trace

echo "simulating 8KB, 2-way associative, split cache, block size = 4096 bytes, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 4096 -a 2 -wb -wa tex.trace