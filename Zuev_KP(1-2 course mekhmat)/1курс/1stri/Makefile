CC=gcc
CFLAGS= -g

all: do-test clean

sum.o: zamena.c zamena.h
#	gcc -c zamena.c

sum_test.o: test1.o zamena.h
#	gcc -c test1.c

a.out: test1.o zamena.o
	gcc test1.o zamena.o -lm

do-test: a.out
	./a.out

clean: test1.o zamena.o
	rm test1.o zamena.o
