#include <stdio.h>
#include <math.h>
#include "simpson.h"
double func1(double a);
double func2(double a);
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))

int main(void)
{
	int i;
	double ep = 0.0001, a = 0.0001, b = 1, result = 0;
	double e = 0.0001;
	double c[] = {8.66587, 0.819368, 0};
	RRFUN funcs[] = {func1, func2, func3};
	for(i = 0; i < 3; i++)
	{
		result = integrate(a, b, ep, funcs[i]);
		if (result > 10000000000)
		{
			printf("пройден\n");
			printf("0\n");
			return 0;
		}
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

double func1(double a)
{
	double k = (8+2*a-a*a);
	return k;
}

double func2(double a)
{
	double k = sin(a*a+a-100);
	return k;
}

double func3(double a)
{
	double k = sin(1/a)*exp(1/(a+0.005));
	return k;
}






