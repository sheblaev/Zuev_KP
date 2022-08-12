#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "func.h"
#include <chrono>
using namespace std;
double norma(double *mas, double *b, double *x, int n);

int main(int argc, char *argv[])
{
	int n, m, p, r, s1, i, j;
	char *filename = 0;
	double q = 1;
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
	double *mas = new double[n*n];
	double *b = new double[n];
	double *mas5 = new double[n*n];
	double *b5 = new double[n];
	double *x = new double[n];
	if (p == 1)
	{
		vvod(mas, s1, n, filename);
		vvod(mas5, s1, n, filename);
		for(i = 0; i < n; i++)
		{
			b[i] = 0;
			b5[i] = 0;
			for(j = 0; j < (n+1)/2; j++)
			{
				b[i] = b[i]+mas[n*i+(2*j)];
				b5[i] = b5[i]+mas5[n*i+(2*j)];
			}
		}
	}
	for(i = 0; i < n; i++)
	{
		x[i] = 0;
	}
	auto t0 = std::chrono::high_resolution_clock::now();
	x = gauss(n, m, s1, p, mas, b, x, filename, r, mas5, b5);
	auto t1 = std::chrono::high_resolution_clock::now();
	auto d = std::chrono::duration_cast<std::chrono::microseconds>( t1 - t0 ).count();
	elapsed = d*0.000001;
	clock_t start1 = clock();
	if (n <= 14)
	{
		q = 0;
		for(i = 0; i < n; i++)
		{
			q = q+modul(x[i]);
		}
	}
	if (q <= 5.0e-300)
	{
		residual = 0;
	}
	else
	{
		residual = norma(mas5, b5, x, n);
	}
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
	printf ("%s : residual = %e elapsed = %.2f for s = %d n = %d m = %d p = %d\n",  argv[0], residual, elapsed, s1, n, m, p);
	delete[] mas;
	delete[] b;
	delete[] mas5;
	delete[] b5;
	delete[] x;
	return 0;
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
