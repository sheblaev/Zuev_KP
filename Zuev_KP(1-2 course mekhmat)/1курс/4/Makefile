CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: sin.c sin.h
#	gcc -c sin.c

sum_test.o: testsin.o sin.h
#	gcc -c testsin.c

a.out: testsin.o sin.o
	gcc testsin.o sin.o -lm

do-test: a.out
	./a.out

clean: testsin.o sin.o
	rm testsin.o sin.o
