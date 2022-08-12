CC=gcc
CFLAGS= -g

all: do-test clean

sum.o: clin.c clin.h
#	gcc -c clin.c

sum_test.o: test4.o clin.h
#	gcc -c test4.c

a.out: test4.o clin.o
	gcc test4.o clin.o -lm

do-test: a.out
	./a.out

clean: test4.o clin.o
	rm test4.o clin.o
