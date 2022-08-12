all: do-test clean

func.o: s.cpp
#	g++ -c s.cpp

test.o: test.cpp
#	g++ -c test.cpp

a.out: test.o s.o
	g++ test.o s.o -lm

do-test: a.out
	./a.out

clean: test.o s.o
	rm test.o s.o
