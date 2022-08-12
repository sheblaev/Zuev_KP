#include <stdio.h>
#include <math.h>
#include "11.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))

int main(void)
{
	int i;
	double ep = 0.0001, a = 0, b = 10, result = 0, alpha = 6;
	double e = 0.1;
	double c[] = {4.809};
	for(i = 0; i < 1; i++)
	{
		result = uravn(a, b, ep, alpha);	
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

