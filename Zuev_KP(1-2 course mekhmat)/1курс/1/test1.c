#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rank.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
double modul(double x);

int main(void)
{
	int i, j, n_rows = 3, n_cols = 5;
	double current, e = 0.1;
	double *mas = malloc(n_rows*n_cols* sizeof(double));
	double result;
	double b[] = {2};
	FILE *input1;
	if((input1 = fopen("input1.txt", "r")) == NULL)
	{
		return -1;
	}
	for(i = 0; i < n_rows*n_cols ; i ++)
	{
		fscanf(input1, "%lf", &current);
		mas[i] = current;
	}
	result = rank(mas, n_rows, n_cols);
		printf( "%lf\n", result);
	for(i = 0; i < 1; i++)
	{
		if (modul(result - b[i]) < e*MAX1(result, b[i], 1))
		{
			printf("пройден\n");
		}
		else
		{
			printf("не пройден\n");
		}
	}
	free(mas);
	fclose(input1);
	return 0;
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}

