#!/bin/bash
echo "simulating 4 byte, fully associative, split cache, write back, write allocate
"
./sim -is 4 -ds 4 -bs 4 -a 1 -wb -wa spice.trace

echo "simulating 8 byte, fully associative, split cache, write back, write allocate
"
./sim -is 8 -ds 8 -bs 4 -a 2 -wb -wa spice.trace

echo "simulating 16 byte, fully associative, split cache, write back, write allocate
"
./sim -is 16 -ds 16 -bs 4 -a 4 -wb -wa spice.trace

echo "simulating 32 byte, fully associative, split cache, write back, write allocate
"
./sim -is 32 -ds 32 -bs 4 -a 8 -wb -wa spice.trace

echo "simulating 64 byte, fully associative, split cache, write back, write allocate
"
./sim -is 64 -ds 64 -bs 4 -a 16 -wb -wa spice.trace

echo "simulating 128 byte, fully associative, split cache, write back, write allocate
"
./sim -is 128 -ds 128 -bs 4 -a 32 -wb -wa spice.trace

echo "simulating 256 byte, fully associative, split cache, write back, write allocate
"
./sim -is 256 -ds 256 -bs 4 -a 64 -wb -wa spice.trace

echo "simulating 512 byte, fully associative, split cache, write back, write allocate
"
./sim -is 512 -ds 512 -bs 4 -a 128 -wb -wa spice.trace

echo "simulating 1024 byte, fully associative, split cache, write back, write allocate
"
./sim -is 1024 -ds 1024 -bs 4 -a 256 -wb -wa spice.trace

echo "simulating 2048 byte, fully associative, split cache, write back, write allocate
"
./sim -is 2048 -ds 2048 -bs 4 -a 512 -wb -wa spice.trace

echo "simulating 4096 byte, fully associative, split cache, write back, write allocate
"
./sim -is 4096 -ds 4096 -bs 4 -a 1024 -wb -wa spice.trace

echo "simulating 8192 byte, fully associative, split cache, write back, write allocate
"
./sim -is 8192 -ds 8192 -bs 4 -a 2048 -wb -wa spice.trace

echo "simulating 16384 byte, fully associative, split cache, write back, write allocate
"
./sim -is 16384 -ds 16384 -bs 4 -a 4096 -wb -wa spice.trace

echo "simulating 32678 byte, fully associative, split cache, write back, write allocate
"
./sim -is 32768 -ds 32768 -bs 4 -a 8192 -wb -wa spice.trace

echo "simulating 65536 byte, fully associative, split cache, write back, write allocate
"
./sim -is 65536 -ds 65536 -bs 4 -a 16384 -wb -wa spice.trace