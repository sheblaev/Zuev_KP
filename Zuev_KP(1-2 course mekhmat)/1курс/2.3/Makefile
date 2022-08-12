CC=gcc 
CFLAGS=-g

all: do-test clean

func.o: simpson.c simpson.h
#	gcc -c simpson.c 

test.o: test23.o simpson.h
#	gcc -c test23.c 

a.out: test23.o simpson.o
	gcc test23.o simpson.o -lm

do-test: a.out
	./a.out 

clean: test23.o simpson.o
	rm test23.o simpson.o 
