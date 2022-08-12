FLAGS = -fsanitize=address -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
all: do-test clean

vvod.o: vvod.cpp func.h
#	g++ -c $(FLAGS) -03 vvod.cpp

gauss.o: gauss.cpp func.h
#	g++ -c $(FLAGS) -03 gauss.cpp

test.o: test.cpp func.h
#       g++ -c $(FLAGS) -03 test.cpp

a.out: test.o gauss.o vvod.o
	g++ -Wextra -Wall -Wfloat-equal test.o gauss.o vvod.o -lm

do-test: a.out

clean: test.o gauss.o vvod.o
	rm test.o gauss.o vvod.o
