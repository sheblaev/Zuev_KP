#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "func.h"
#include <chrono>
using namespace std;
void vyvod(double *mas, int l, int n);
double norma(double *mas, double *b, double *x, int n);

int main(int argc, char *argv[])
{
	int n, m, r, s, i, k;
	char *filename = 0;
	double q = 0;
	if (!(argc == 5 || argc == 6) || sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1 || sscanf(argv[3], "%d", &r) != 1 || sscanf(argv[4], "%d", &s) != 1)
	{
		printf("Usage: %s n m r s input1", argv[0]);
		return 1;
	}
	if (argc == 6)
		filename = argv[5];
	double residual, elapsed;
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	r = atoi(argv[3]);
	s = atoi(argv[4]);
	double *mas = new double[n*n];
	double *b = new double[n];
	double *mas1 = new double[n*n];
	double *b1 = new double[n];
	double *x = new double[n];
	vvod(mas, s, n, filename);
	vvod(mas1, s, n, filename);
	for(i = 0; i < n*n; i++)
	{
		q=q+modul(mas[i]);
	}
	if ((q <= 5.0e-300) && (n != 1))
	{
		printf("В файле меньше элементов чем заявлено\n");
	}
	if ((q >= 5.0e-300) || (n == 1))
	{
		for(i = 0; i < n; i++)
		{
			b[i] = 0;
			b1[i] = 0;
			x[i] = 0;
			for(k = 0; k < (n+1)/2; k++)
			{
				b[i] = b[i]+mas[n*i+(2*k)];
				b1[i] = b1[i]+mas[n*i+(2*k)];
			}
		}
		if (r < n)
		{
			for(i = 0; i < r; i++)
			{
				printf("%10.3e\n", b[i]);
			}
		}
		else
		{
			for(i = 0; i < n; i++)
			{
				printf("%10.3e\n", b[i]);
			}
		}
		printf("\n");
		vyvod(mas, r, n);
		auto t0 = std::chrono::high_resolution_clock::now();
		x = gauss(n, m, mas, b, x);
		auto t1 = std::chrono::high_resolution_clock::now();
		auto d = std::chrono::duration_cast<std::chrono::microseconds>( t1 - t0 ).count();
		elapsed = d*0.000001;
		clock_t start1 = clock();
		residual = norma(mas1, b1, x, n);
		clock_t end1 = clock();
		double seconds = (double)(end1 - start1) / CLOCKS_PER_SEC;
		if (r < n)
		{
			for(i = 0; i < r; i++)
			{
				printf("%10.3e\n", x[i]);
			}
		}
		else
		{
			for(i = 0; i < n; i++)
			{
				printf("%10.3e\n", x[i]);
			}
		}
		printf("Время, затраченное на вычисление невязки: %f\n", seconds);
		printf ("%s : residual = %e elapsed = %.2f for s = %d n = %d m = %d\n",  argv[0], residual, elapsed, s, n, m);
	}
	delete[] mas;
	delete[] b;
	delete[] mas1;
	delete[] b1;
	delete[] x;
	return 0;
}

void vyvod(double *mas, int l, int n)
{
	int i, j;
	if (l < n)
	{
		for ( i = 0; i < l; i++)
		{
			for ( j = 0; j < l; j++)
			{
				printf("%10.3e", mas[n*i+j]);
			}
			printf("\n");
		}
	}
	else
	{
		for ( i = 0; i < n; i++)
		{
			for ( j = 0; j < n; j++)
			{
				printf("%10.3e", mas[n*i+j]);
			}
			printf("\n");
		}
	}
}

double norma(double *mas, double *b, double *x, int n)
{
	int i, j;
	double s = 0, p = 0;
	double *c = new double[n];
	for (i = 0; i < n; i++)
	{
		c[i] = 0;
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			c[i] = c[i]+mas[n*i+j]*x[j];
		}
	}
	for ( i = 0; i < n; i++)
	{
		s = s+modul(c[i]-b[i]);
	}
	for ( i = 0; i < n; i++) 
	{
		p = p+modul(b[i]);
	}
	delete[] c;
	return s/p;
}
