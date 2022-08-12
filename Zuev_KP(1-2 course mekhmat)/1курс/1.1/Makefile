CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: delenie.c delenie.h
#	gcc -c delenie.c

sum_test.o: test11.o delenie.h
#	gcc -c test11.c

a.out: test11.o delenie.o
	gcc test11.o delenie.o -lm

do-test: a.out
	./a.out

clean: test11.o delenie.o
	rm test11.o delenie.o
