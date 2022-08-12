#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "clin.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
double modul(double x);

int main(void)
{
	int row, i, j, n_rows = 3, n_cols = 4;
	double current, e = 0.1;
	double **mas = malloc(n_rows* sizeof(double));
	double *x = malloc(n_rows* sizeof(double));
	double b[] = {4.05, -0.72, -3.7};
	FILE *input1;
	if((input1 = fopen("input1.txt", "r")) == NULL)
	{
		return -1;
	}
	for(row = 0; row < n_rows; row++)
	{
		mas[row] = malloc(n_cols* sizeof(double));
	}
	for(i = 0; i < n_rows ; i ++)
	{
		for(j = 0; j < n_cols; j ++)
		{
			fscanf(input1, "%lf", &current);
			mas[i][j] = current;
		}
	}
	x = clin(mas, n_rows, n_cols, x);
	for ( i = 0; i < n_rows; i++ )
		printf( "%lf\n", x[i] );
	for(i = 0; i < n_rows; i++)
	{
		if (modul(x[i] - b[i]) < e*MAX1(x[i], b[i], 1))
		{
			printf("пройден\n");
		}
		else
		{
			printf("не пройден\n");
		}
	}
	for(row = 0; row < n_rows; row ++)
	{
		free(mas[row]);
	}
	free(x);
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
