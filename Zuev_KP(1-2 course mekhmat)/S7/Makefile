all: do-test clean

Data.o: Data.cpp Data.h
#	g++ -c Data.cpp

a.out: Data.o
	g++ Data.o -lm

do-test: a.out
	./a.out

clean: Data.o
	rm Data.o
