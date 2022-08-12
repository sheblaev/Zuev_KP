CC=gcc 
CFLAGS=-g

all: do-test clean

func.o: zoloto.c zoloto.h
#	gcc -c zoloto.c 

test.o: test32.o zoloto.h
#	gcc -c test32.c 

a.out: test32.o zoloto.o
	gcc test32.o zoloto.o -lm

do-test: a.out
	./a.out 

clean: test32.o zoloto.o
	rm test32.o zoloto.o 
