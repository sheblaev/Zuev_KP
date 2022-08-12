all: do-test clean

func.o: func.cpp func.h
#	g++ -c func.cpp

test.o: test.cpp func.h
#       g++ -c test.cpp

a.out: test.o func.o
	g++ test.o func.o -pthread

do-test: a.out

clean: test.o func.o
	rm test.o func.o
