#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <cmath>
#include "func.h"
using namespace std;
void vyvod(double *mas, int l, int n);
double norma0(double *mas, double *x, int n);
double norma1(double *mas, double *x, int n);

int main(int argc, char *argv[])
{
	int i, j, n = 0, m = 0, k = 0, its = 0, z = 0;
	char *filename = 0;
	double e = 0, q = 0, res1  = 0, res2 = 0, t1 = 0, t2 = 0;
	if (!(argc == 5 || argc == 6) || sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1 || sscanf(argv[3], "%lf", &e) != 1 || sscanf(argv[4], "%d", &k) != 1)
	{
		printf("Usage: %s n m r s input1", argv[0]);
		return 1;
	}
	if (argc == 6)
		filename = argv[5];
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	e = atof(argv[3]);
	k = atoi(argv[4]);
	double *mas = new double[n*n];
	double *x = new double[n];
	vvod(mas, k, n, filename);
	for(i = 0; i < n*n; i++)
	{
		q=q+fabs(mas[i]);
	}
	if ((q <= 5.0e-300) && (n != 1))
	{
		printf("В файле меньше элементов чем заявлено\n");
	}
	if ((q >= 5.0e-300) || (n == 1))
	{
		for(i = 0; i < n; i++)
		{
			x[i] =0;
		}
		vyvod(mas, m, n);
		for (i=0; i<n; i++)
		{
			for (j=i+1; j<n; j++)
			{
				if (fabs(mas[i*n+j]-mas[j*n+i]) > 1.110223e-16)
				{
					z = 1;
				}
			}
		}
		if (z == 1)
		{
			printf("несимметричная\n");
			delete[] mas;
			delete[] x;
			return 0;
		}
		clock_t start1 = clock();
		mas = rotation(n, mas, e);
		clock_t end1 = clock();
		double t1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
		auto t_0 = std::chrono::high_resolution_clock::now();
		its = bisection(n, mas, x, e);
		auto t_1 = std::chrono::high_resolution_clock::now();
		auto d = std::chrono::duration_cast<std::chrono::microseconds>( t_1 - t_0 ).count();
		double t2 = d*0.000001;
		if (m < n)
		{
			for(i = 0; i < m; i++)
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
		res1 = norma0(mas, x, n);
		res2 = norma1(mas, x, n);
		printf ("%s : Residual1 = %e Residual2 = %e Iterations = %d Iterations1 = %d Elapsed1 = %.2f Elapsed2 = %.2f\n", argv[0], res1, res2, its, its / n, t1, t2);
	} 
	delete[] mas;
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

double norma0(double *mas, double *x, int n)
{
	int i, j;
	double s = 0, p = 0, norma = 0, max = 0;
	for (i = 0; i < n; i++)
	{
		s = s+mas[n*i+i];
		p = p+x[i];
	}
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < n; i++)
		{
			max = max+fabs(mas[n*i+j]);
		}
		if (max > norma)
		{
			norma = max;
		}
	}
	return (fabs(s-p))/(norma);
}

double norma1(double *mas, double *x, int n)
{
	int i, j;
	double s = 0, p = 0, norma = 0, max = 0;
	for (i = 0; i < n; i++)
	{
		p = p+x[i]*x[i];
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			s = s+mas[n*i+j]*mas[n*j+i];
		}
	}
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < n; i++)
		{
			max = max+fabs(mas[n*i+j]);
		}
		if (max > norma)
		{
			norma = max;
		}
	}
	return (fabs(sqrt(s)-sqrt(p)))/(norma);
}
