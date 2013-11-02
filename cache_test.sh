#!/bin/bash
#Script that tests all cache simulations on spice.trace according to Table 1 in the Project 3 description

make
echo "
1. Testing 8KB split cache, block size = 16 bytes, associativity = 1, WB, WA
"
./sim -is 8192 -ds 8192 -bs 16 -a 1 -wb -wa spice.trace

echo "
2. Testing 16KB split cache, block size = 16 bytes, associativity = 1, WB, WA
"
./sim -is 16384 -ds 16384 -bs 16 -a 1 -wb -wa spice.trace

echo "
3. Testing 32KB split cache, block size = 16 bytes, associativity = 1, WB, WA
"
./sim -is 32768 -ds 32768 -bs 16 -a 1 -wb -wa spice.trace

echo "
4. Testing 64KB split cache, block size = 16 bytes, associativity = 1, WB, WA
"
./sim -is 65536 -ds 65536 -bs 16 -a 1 -wb -wa spice.trace

echo "
5. Testing 8KB unified cache, block size = 16 bytes, associativity = 1, WB, WA
"
./sim -us 8192 -bs 16 -a 1 -wb -wa spice.trace

echo "
6. Testing 8KB unified cache, block size = 32 bytes, associativity = 1, WB, WA
"
./sim -us 8192 -bs 32 -a 1 -wb -wa spice.trace

echo "
7. Testing 8KB unified cache, block size = 64 bytes, associativity = 1, WB, WA
"
./sim -us 8192 -bs 64 -a 1 -wb -wa spice.trace

echo "
8. Testing 32KB split cache, block size = 128 bytes, associativity = 1, WB, WA
"
./sim -is 32768 -ds 32768 -bs 128 -a 1 -wb -wa spice.trace

echo "
9. Testing 8KB split cache, block size = 64 bytes, associativity = 2, WB, WA
"
./sim -is 8192 -ds 8192 -bs 64 -a 2 -wb -wa spice.trace

echo "
10. Testing 8KB split cache, block size = 64 bytes, associativity = 4, WB, WA
"
./sim -is 8192 -ds 8192 -bs 64 -a 4 -wb -wa spice.trace

echo "
11. Testing 8KB split cache, block size = 64 bytes, associativity = 8, WB, WA
"
./sim -is 8192 -ds 8192 -bs 64 -a 8 -wb -wa spice.trace

echo "
12. Testing 8KB split cache, block size = 64 bytes, associativity = 16, WB, WA
"
./sim -is 8192 -ds 8192 -bs 64 -a 16 -wb -wa spice.trace

echo "
13. Testing 8KB split cache, block size = 64 bytes, associativity = 128, WB, WA
"
./sim -is 8192 -ds 8192 -bs 64 -a 128 -wb -wa spice.trace

echo "
14. Testing 1KB split cache, block size = 64 bytes, associativity = 2, WB, WA
"
./sim -is 1024 -ds 1024 -bs 64 -a 2 -wb -wa spice.trace

echo "
15. Testing 1KB split cache, block size = 64 bytes, associativity = 8, WB, WA
"
./sim -is 1024 -ds 1024 -bs 64 -a 8 -wb -wa spice.trace

echo "
16. Testing 1KB split cache, block size = 64 bytes, associativity = 16, WB, WA
"
./sim -is 1024 -ds 1024 -bs 64 -a 16 -wb -wa spice.trace

echo "
17. Testing 8KB split cache, block size = 16 bytes, associativity = 1, WT, WA
"
./sim -is 8192 -ds 8192 -bs 16 -a 1 -wt -wa spice.trace

echo "
18. Testing 8KB split cache, block size = 32 bytes, associativity = 1, WT, WA
"
./sim -is 8192 -ds 8192 -bs 32 -a 1 -wt -wa spice.trace

echo "
19. Testing 8KB split cache, block size = 64 bytes, associativity = 2, WT, WA
"
./sim -is 8192 -ds 8192 -bs 64 -a 2 -wt -wa spice.trace

echo "
20. Testing 8KB split cache, block size = 16 bytes, associativity = 1, WB, WNA
"
./sim -is 8192 -ds 8192 -bs 16 -a 1 -wb -nw spice.trace

echo "
21. Testing 8KB split cache, block size = 32 bytes, associativity = 1, WB, WNA
"
./sim -is 8192 -ds 8192 -bs 32 -a 1 -wb -nw spice.trace

echo "
22. Testing 8KB split cache, block size = 64 bytes, associativity = 2, WB, WNA
"
./sim -is 8192 -ds 8192 -bs 64 -a 2 -wb -nw spice.trace