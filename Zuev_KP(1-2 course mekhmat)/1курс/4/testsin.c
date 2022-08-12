#include <stdio.h>
#include <math.h>
#include "sin.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
#define pi 3.141592653589793238462643383279
double func1(double x);
double modul(double x);

int main(void)
{
	int i;
	double ep = 1e-100, result = 0;
	double e = 0.01;
	double x[] = {pi/6, pi/32, 0.1, 88, -15};
	double b[] = {0.5, 0.098, 0.0998, 0.0354, -0.65};
	for(i = 0; i < 5; i++)
	{
		while ((x[i] > 0) && (x[i] > 2*pi))
		{
			x[i] = x[i] - 2*pi;
		}
		while ((x[i] < 0) && (modul(x[i]) > 2*pi))
		{
			x[i] = x[i] + 2*pi;
		}
		result = taylor(x[i], ep, func1);
		if (modul(result - b[i]) < e*MAX1(result, b[i], 1))
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
	double k = sin(x);
	return k;
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
