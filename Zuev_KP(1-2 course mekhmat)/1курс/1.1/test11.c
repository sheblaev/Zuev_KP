#include <stdio.h>
#include <math.h>
#include "delenie.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
double func1(double a);
double func2(double a);
double modul(double x);

int main(void)
{
	int i;
	double ep = 0.0001, a = 0.5, b = 4, result = 0;
	double e = 0.0001;
	double c[] = {0, 1};
	ErrorCode ec;
	RRFUN funcs[] = {func1, func2};
	for(i = 0; i < 2; i++)
	{
		result = delenie(a, b, ep, funcs[i], &ec);
		if(ec != SF_OK)
		{
			printf("error\n");
		
		}
		else
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
	double k = (8+2*a);
	return k;
}

double func2(double a)
{
	double k = (a*a+a-2);
	return k;
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
