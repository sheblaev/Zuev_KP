#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EL(m, n_cols, row, col) \
    ((m)[(n_cols) * (row) + col])
double *vbr(double *mas, int n_rows, int n_cols);
double modul(double x);

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}

double *vbr(double *mas, int n_rows, int n_cols)
{
	int k = 0, j = 0, i = 0, m = 0, ind;
	double t = 0, s = 0, d = 0, max = 0;
	for(i = 0; i < n_rows*n_cols ; i ++)
	{
		if (mas[i] == 0)
			s = s+1;
	}
	if (s == n_rows*n_cols)
		return mas;
	for (k = 0; k < n_rows; k ++)
	{
		s = 0;
		for (i = 0; i < n_cols; i ++)
		{
			t = EL(mas, n_cols, k, 0);
			d = EL(mas, n_cols, k, i);
			if (modul(d)>modul(t)) 
			{
				s = s+d;
			}
		}
		if (s>max)
		{			
			max = s;
			m = k;
		}
	}
	for (k = 0; k < n_rows; k ++)
	{
		ind = 0;
		s = 0;
		for (i = 0; i < n_cols; i ++)
		{
			if (ind == 0)
			{
				for (j = 0; j < n_cols; j ++)
				{
					s = s+EL(mas, n_cols, k, j);
				}
			}
			if (s != 0)
			{
				mas[(n_cols)*(k)+i] = EL(mas, n_cols, m, i)*n_cols/s;
			}
			ind = 1;
		}
	}
	return mas;
}

int main(void)
{
	int row, i, j, n_rows = 0, n_cols = 0;
	double current;
	double *mas;
	FILE *input1, *result;
	if ((input1 = fopen("input1.txt", "r")) == NULL)
	{
		return -1;
	}
	if ((result = fopen("result.txt", "w")) == NULL)
	{
		return -1;
	}
	if (fscanf(input1, "%d", &n_rows)!=1)
	{
		return -1;
	}
	if (fscanf(input1, "%d", &n_cols)!=1)
	{
		return -1;
	}
	if (n_rows < 1)
	{
		return -1;
	}
	if (n_cols < 1) 
	{
		return -1;
	}
	mas = malloc(n_rows*n_cols* sizeof(double));
	if (mas == NULL)
		return -1;
	for(i = 0; i < n_rows*n_cols ; i ++)
	{
		fscanf(input1, "%lf", &current);
		mas[i] = current;
	}
	mas = vbr(mas, n_rows, n_cols);
	for(j = 0; j < n_cols*n_rows; j ++)
	{
		fprintf(result, "%lf\n", mas[j]);
        }
	free(mas);
	fclose(input1);
	fclose(result);
	return 0;	
}
