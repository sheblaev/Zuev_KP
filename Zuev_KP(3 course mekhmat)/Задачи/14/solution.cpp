#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "func.h"
using namespace std;
int ab(double *mas, double *x, int n, double e, double a, double b, int &its, int &k, double max);
double *umnoz(double *b, double *c, double *d, int r0, int c0, int c1);

double *rotation(int n, double *mas, double e)
{
	int i, j, k, z = 0;
	double *t = new double[n*n];
	double c = 0, s = 0, sum = 0;
	for (i = 0; i < n-2; i++)
	{
		for (j = i+2; j < n; j++)
		{
			sum = sum+mas[i*n+j];
			if (sum >= 5.0e-300)
			{
				break;
			}
		}
		if (sum >= 5.0e-300)
		{
			break;
		}
	}
	if (sum < 5.0e-300)
	{
		z = 1;
	}
	if (z == 0)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i == j)
				{
					t[i*n+j] = 1;
				}
				else
				{
					t[i*n+j] = 0;
				}
			}
		}
		for (k = 1; k <= (n-2)*(n-1)/2; k++)
		{
			for (i = 1; i < n-1; i++)
			{
				for (j = i+1; j < n; j++)
				{
					if ((fabs(mas[(i-1)*n+i]) > pow(e, 2)) || (fabs(mas[(i-1)*n+j]) > pow(e, 2)))
					{
						if (fabs(mas[(i-1)*n+i]) > pow(e, 2))
						{
							if (fabs(mas[(i-1)*n+j]) > pow(e, 2))
							{
								c = mas[(i-1)*n+i]/sqrt(pow(mas[(i-1)*n+i], 2)+pow(mas[(i-1)*n+j], 2));
							}
							else
							{
								c = mas[(i-1)*n+i]/sqrt(pow(mas[(i-1)*n+i], 2));
							}
						}
						else
						{
							c = 0;
						}
						if (fabs(mas[(i-1)*n+j]) > pow(e, 2))
						{
							if (fabs(mas[(i-1)*n+i]) > pow(e, 2))
							{
								s = -mas[(i-1)*n+j]/sqrt(pow(mas[(i-1)*n+i], 2)+pow(mas[(i-1)*n+j], 2));
							}
							else
							{
								s = -mas[(i-1)*n+j]/sqrt(pow(mas[(i-1)*n+j], 2));
							}
						}
						else
						{
							s = 0;
						}
						t[i*n+i] = c;
						t[j*n+j] = c;
						t[i*n+j] = -s;
						t[j*n+i] = s;
						mas = umnoz(mas, t, mas, n, n, n);
						t[i*n+i] = c;
						t[j*n+j] = c;
						t[i*n+j] = s;
						t[j*n+i] = -s;
						mas = umnoz(mas, mas, t, n, n, n);
						t[i*n+i] = 1;
						t[j*n+j] = 1;
						t[i*n+j] = 0;
						t[j*n+i] = 0;
					}
				}
			}
		}
	}
	delete[] t;
	return mas;
}

int bisection(int n, double *mas, double *x, double e)
{
	double a0 = 0, b0 = 0, c = 0, max0 = 0, max1 = 0;
	int i, j, n_ = 0, i1 = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			max0 = max0+fabs(mas[i*n+j]);
		}
		if (max0 > max1)
		{
			max1 = max0;
		}
		max0 = 0;
	}
	a0 = -max1;
	b0 = max1;
	ab(mas, x, n, e, a0, b0, n_, i1, max1);
	if (i1 != n)
	{
		printf("Количество собственных значений меньше n\n");
		return 0;
	}
	return n_;
}

int ab(double *mas, double *x, int n, double e, double a, double b, int &its, int &k, double max)
{
	int i, z = 0;
	z = number(n, mas, b, max)-number(n, mas, a, max);
	if (((b-a) > e*max) && (z != 0))
	{
		its++;
		ab(mas, x, n, e, a, (a+b)/2, its, k, max);
		ab(mas, x, n, e, (a+b)/2, b, its, k, max);
	}
	else
	{
		if (z != 0)
		{
			for (i=k; i<k+z; i++) 
			{
				x[i] = (a+b)/2;
			}
			k = k+z;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

int number(int n, double *mas, double l, double max)
{
	int i, k, n1 = 0, m = 0;
	double x = 0, y = 0, a = 0, b = 0, g = 0, u = 0, v = 0, a_ = 0, max0 = 0, max1 = 0, eps = 1.110223e-16;
	for (i = 0; i < n; i++)
	{
		if (fabs(mas[i*n+i]-l) > max0)
		{
			max0 = fabs(mas[i*n+i]-l);
		}
		if (i > 0)
		{
			if (fabs(mas[i*n+(i-1)]) > max1)
			{
				max1 = fabs(mas[i*n+(i-1)]);
			}
		}
	}
	if (max0 > max1)
	{
		a_ = 4*max0;
	}
	else
	{
		a_ = 4*max1;
	}
	if (a_ < 5.0e-300)
	{
		return m;
	}
	for (k = 0; k < n; k++)
	{
		if (k == 0)
		{
			x = (mas[k*n+k]-l)/(a_);
			y = 1;
			if (x*y < 0)
			{
				m = 1;
			}
			else
			{
				m = 0;
			}
		}
		else
		{
			a = (mas[k*n+k]-l)/(a_);
			b = (mas[k*n+k-1])/(a_);
			if (fabs(x) > fabs(b*(b*y)))
			{
				g = (1/eps)/(fabs(x));
			}
			else
			{
				g = (1/eps)/(fabs(b*(b*y)));
			}
			u = g*(a*x-b*(b*y));
			v = g*x;
			if (fabs(x) < 5.0e-300)
			{
				m = m+1;
			}
			else
			{
				if (u*x < 0)
				{
					m = m+1;
				}
			}
			x = u;
			y = v;
		}
	}
	return m;
}

double *umnoz(double *b, double *c, double *d, int r0, int c0, int c1)
{
	double *a = new double[r0*c1];
	double q = 0;
	for (int i = 0; i < r0; i++)
	{
		for (int j = 0; j < c1; j++)
		{
			a[i*c1+j] = 0;
		}
	}
	for (int i = 0; i < r0; i++)
	{
		for (int k = 0; k < c0; k++) 
		{
			q = c[i*c0+k];
			for (int j = 0; j < c1; j++)
			{
				a[i*c1+j] += q*d[k*c1+j];
			}
		}
	}	
	for (int i = 0; i < r0; i++)
	{
		for (int j = 0; j < c1; j++)
		{
			b[i*c1+j] = a[i*c1+j];
		}
	}
	delete[] a;
	return b;
}
