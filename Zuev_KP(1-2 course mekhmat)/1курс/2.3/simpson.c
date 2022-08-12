#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"simpson.h"
static double simp(double a, double b, double ep, RRFUN ffunc);

static double simp(double a, double b, double n, RRFUN ffunc)
{
	int i;
	double h = 0, res1 = 0, res2 = 0, res = 0, x = 0, i1 = 0, i2 = 0, k = 1;
	h = (b-a)/(2*n);
	for(i = 1; i < n-1; i++)
	{
		x = a+2*i*h;
		res1 = res1 + (*ffunc)(x);
	}
	for(i = 1; i < n; i++)
	{
		x = a+(2*i-1)*h;
		res2 = res2 + (*ffunc)(x);
	}
	res = (h/3)*(2*res1 + 4*res2 + (*ffunc)(a) + (*ffunc)(b));
	return res;
}

double integrate(double a, double b, double ep, RRFUN ffunc)
{
	int n = 2;
	double i1 = simp(a, b, n, ffunc), i2 = simp(a, b, 2*n, ffunc);
	while ((n > 0) && (modul(i2 - i1) > ep) && (n < 67108864))
	{                                              
		i1 = simp(a, b, n, ffunc);
		n = 2*n;
		i2 = simp(a, b, n, ffunc);
	}
	return i2;
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
