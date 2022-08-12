#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "func.h"
using namespace std;

void vvod(double *mas, int s, int n, char *a)
{
	int i = 0, j, l = 0, q = 0;
	double z = 0;
	q = n*n;
	if (s == 0)
	{
		FILE *f;
		f = fopen(a, "r");
		while(fscanf(f, "%lf", &z) == 1)
		{
			l = l+1;
		}
		fclose(f);
		if (l==q)
		{
			z = 0;
			f = fopen(a, "r");
			while (fscanf(f, "%lf", &z) == 1)
			{
				mas[i] = z;
				i = i+1;
			}
			fclose(f);
		}
		else
		{
			for ( i = 0; i < n*n; i++)
                	{
                        	mas[i] = 0;
                	}
		}
	}
	else
	{
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				mas[n*i+j] = func(s, n, i, j);
			}
		}
	}
}

double func(int s, int n, int i, int j)
{
	if (s == 1)
	{
		if (i>=j)
			return n-i+1;
		else
			return n-j+1;
	}
	if (s == 2)
	{
		if (i>=j)
			return i;
		else
			return j;
	}
	if (s == 3)
	{
		return modul(i-j);
	}
	if (s == 4)
	{
		double k;
		k = static_cast<double>(i+j+1);
			return 1/k;
	}
	return 0;
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else
		return x;
}
