#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "func.h"
#include <chrono>
using namespace std;

int main(int argc, char *argv[])
{
	int n, m, p, r, s1, i, j;
	char *filename = 0;
	if (!(argc == 6 || argc == 7) || sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1 || sscanf(argv[3], "%d", &p) != 1 || sscanf(argv[4], "%d", &r) != 1 || sscanf(argv[5], "%d", &s1) != 1)
	{
		printf("Usage: %s n m r s input1", argv[0]);
		return 1;
	}
	if (argc == 7)
		filename = argv[6];
	double residual = 0, elapsed = 0;
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	p = atoi(argv[3]);
	r = atoi(argv[4]);
	s1 = atoi(argv[5]);
	residual = 0;
	elapsed = 0;
	printf ("%s : residual = %e elapsed = %.2f for s = %d n = %d m = %d p = %d\n",  argv[0], residual, elapsed, s1, n, m, p);
	return 0;
}
