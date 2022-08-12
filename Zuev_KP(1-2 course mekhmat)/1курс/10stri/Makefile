CC=gcc
CFLAGS= -g

all: do-test clean

sum.o: def.c def.h
#	gcc -c def.c

sum_test.o: test10.o def.h
#	gcc -c test10.c

a.out: test10.o def.o
	gcc test10.o def.o -lm

do-test: a.out
	./a.out

clean: test10.o def.o
	rm test10.o def.o
