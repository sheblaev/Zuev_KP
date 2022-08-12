FLAGS = -fsanitize=address -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
all: do-test clean

vrp.o: vrp.cpp
#	g++ -c $(FLAGS) -03 vrp.cpp

a.out: vrp.o
	g++ -Wextra -Wall -Wfloat-equal vrp.o -lm -pthread

do-test: a.out

clean: vrp.o
	rm vrp.o
