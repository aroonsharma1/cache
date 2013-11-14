CC = gcc

all:  sim

sim:  main.o cache.o
	$(CC) -o sim main.o cache.o -lm

main.o:  main.c cache.h
	$(CC) -c main.c

cache.o:  cache.c cache.h
	$(CC) -c cache.c
	