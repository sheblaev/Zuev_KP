FLAGS = -fsanitize=address -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
all: do-test clean

tsp.o: tsp.cpp func.h
#	g++ -c $(FLAGS) -03 tsp.cpp

test.o: test.cpp func.h
#       g++ -c $(FLAGS) -03 test.cpp

a.out: test.o tsp.o
	g++ -Wextra -Wall -Wfloat-equal test.o tsp.o -lm -pthread

do-test: a.out

clean: test.o tsp.o
	rm test.o tsp.o
