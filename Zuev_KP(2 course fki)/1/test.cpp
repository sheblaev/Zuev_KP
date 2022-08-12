#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "func.h"
using namespace std;

int main(int argc, char *argv[])
{
	int i, j = 0, z = 0, l = 0, n = 0, k = 0;
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
	int *x = new int[n+1];
	for (i = 0; i < n; i++)
	{
		w[i] = 0;
		v[i] = 0;
		x[i] = 0;
	}
	x[n] = 0;
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
	x = backpack(n, k, w, v, x);
	for (i = 0; i < n+1; i++)
        {
                printf("%d ", x[i]);
        }
	printf("\n");
	delete[] w;
	delete[] v;
	delete[] x;
	return 0;
}
