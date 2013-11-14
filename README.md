Cache
=====

cache project for ENEE646

When trying to run this simulator on glue, type 'make' at the command line. Then you can run ./cache_test.sh to see all outputs from Table 1 in the project sheet. If the simulator doesn't work on glue, it might be necessary to run each separate command in 'Makefile' separately from the command line. 

In the simulator, the access numbers for each sample trace are off by 1. For example, for spice.trace instruction cache accesses are 782763 when it should actually be 782764. I don't know why this happens. The simulator is processing all memory addresses in each trace file because all other numbers are correct. 
