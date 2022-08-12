CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: rank.c rank.h
#	gcc -c rank.c

sum_test.o: test1.o rank.h
#	gcc -c test1.c

a.out: test1.o rank.o
	gcc test1.o rank.o -lm

do-test: a.out
	./a.out

clean: test1.o rank.o
	rm test1.o rank.o
