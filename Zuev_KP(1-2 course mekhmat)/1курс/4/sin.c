#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"sin.h"
static double modul(double x);

double taylor(double x, double ep, RRFUN ffunc)
{
	double k, s;
	int n = 2;
	k = x;
	s = x;
	while (modul(k)>ep)
	{
		k = -k*x*x/(n*(n+1)); 
		s = s+k;
		n = n+2;
	}
	return s;
}

static double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
