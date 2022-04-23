#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "func.h"
using namespace std;

int main(int argc, char *argv[])
{
	int i, j = 0, z = 0, l = 0, n = 0, k = 0, x = 0;
	char *filename = 0;
	if (argc != 2)
	{
		printf("Usage: %s input\n", argv[0]);
		return 1;
	}
	filename = argv[1];
	FILE *f;
	f = fopen(filename, "r");
	if (fscanf(f, "%d", &z) == 1)
	{
		n = z;
	}
	if (fscanf(f, "%d", &z) == 1)
	{
		k = z;
	}
	int *w = new int[n];
	int *v = new int[n];
	for (i = 0; i < n; i++)
	{
		w[i] = 0;
		v[i] = 0;
	}
	while (fscanf(f, "%d", &z) == 1)
	{
		if (l == 0)
		{
			v[j] = z;
		}
		if (l == 1)
		{
			w[j] = z;
			j = j+1;
			l = 0;
		}
		else
		{
			l = 1;
		}
	}
	fclose(f);
	x = backpack(n, k, w, v);
	printf("%d\n", x);
	delete[] w;
	delete[] v;
	return 0;
}
