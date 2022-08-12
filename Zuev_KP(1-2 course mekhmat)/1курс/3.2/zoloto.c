#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"zoloto.h"
static double modul(double x);

double minimum(double a, double b, double ep, RRFUN ffunc)
{
	double x1, x2, y1, y2, min, x;
	double k = (1+sqrt(5))/2;
	while (modul(b-a) >= ep)
	{
		x1 = b - (b-a)/k;
		x2 = a + (b-a)/k;
		y1 = (*ffunc)(x1);
		y2 = (*ffunc)(x2);
		if (y1 >= y2)
		{
			a = x1;
		}
		else
		{
			b = x2;
		}
		if (modul(b-a) < ep)
		{
			x = (a+b)/2;
		}
	}
	if (((*ffunc)(a)>(*ffunc)(x)) && ((*ffunc)(x)<(*ffunc)(b)))
	{
		min = (*ffunc)(x - ((x-a)*(x-a)*((*ffunc)(x)-(*ffunc)(b))-(x-b)*(x-b)*((*ffunc)(x)-(*ffunc)(a)))/(2*((x-a)*((*ffunc)(x)-(*ffunc)(b))-(x-b)*((*ffunc)(x)-(*ffunc)(a)))));
	}
	else
	{
		min = (*ffunc)(x);
	}
	return min;
}

static double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
