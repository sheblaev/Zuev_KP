#include <stdio.h>
#include <math.h>
#include "zoloto.h"
double modul(double x);
double func1(double x);
double func2(double x);
double func3(double x);
double func4(double x);
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))

int main(void)
{
	int i;
	double ep = 1e-10, a = 0, b = 4, result = 0;
	double e = 0.01;
	double c[] = {8, -1.01002, -1, 0};
	RRFUN funcs[] = {func1, func2, func3, func4};
	for(i = 0; i < 4; i++)
	{
		result = minimum(a, b, ep, funcs[i]);
		if (modul(result - c[i]) < e*MAX1(result, c[i], 1))
		{
			printf("пройден\n");
			printf("%lf\n", result);
		}
		else
		{
			printf("не пройден\n");
			printf("%lf\n", result);
		}
	}

	return 0;
}

double func1(double x)
{
	double k = (8+2*x+x*x);
	return k;
}

double func2(double x)
{
	double k = cos(1/x)*exp(1/(x+100));
	return k;
}

double func3(double x)
{
	double k = cos(x);
	return k;
}

double func4(double x)
{
	double k = x*x*x;
	return k;
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
