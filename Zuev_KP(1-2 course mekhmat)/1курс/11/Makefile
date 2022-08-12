CC=gcc 
CFLAGS=-g

all: do-test clean

func.o: 11.c 11.h
#	gcc -c 11.c 

test.o: test11.o 11.h
#	gcc -c test11.c 

a.out: test11.o 11.o
	gcc test11.o 11.o -lm

do-test: a.out
	./a.out 

clean: test11.o 11.o
	rm test11.o 11.o 
