all: do-test clean

func.o: vector.cpp
#	g++ -c vector.cpp

test.o: test.cpp
#	g++ -c test.cpp

a.out: test.o vector.o
	g++ test.o vector.o -lm

do-test: a.out
	./a.out

clean: test.o vector.o
	rm test.o vector.o
