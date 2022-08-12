#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"rank.h"
#define EL(m, n_cols, row, col) \
    ((m)[(n_cols) * (row) + col])
static double modul(double x);

double rank(double *mas, int n_rows, int n_cols)
{
	int k, j, i;
	double r = n_rows, t = 0, s = 0, d = 0;
	for (k = 0; k < n_rows; k ++)
	{
		for (i = k + 1; i < n_rows; i ++)
		{
			d = EL(mas, n_cols, k, k); 
			if (modul(d) < 0.000001)
				break;
			s = EL(mas, n_cols, i, k)/d;
			for (j = 0; j < n_cols; j ++)
			{
				EL(mas, n_cols, i, j) -= EL(mas, n_cols, k, j) * s;
			}
		}
	}
	for (k = n_rows-1; k >= 1; k --)
	{
		for (i = n_cols-1; i >= 0; i --)
		{
			d = EL(mas, n_cols, k, i); 
			if (modul(d) < 0.000001)
				break;
			EL(mas, n_cols, k-1, i) -= EL(mas, n_cols, k, i)*EL(mas, n_cols, k-1, i)/d;
		}
	}
	for(i = 0; i < n_rows; i++)
	{
		t=0;
		for(j = 0; j < n_cols; j++)
		{
			if(EL(mas, n_cols, i, j) == 0)
			{
				t=t+1;
			}
		}
		if(t == n_cols)
		{
			r=r-1;
		}
	}
	if (r == 0)
		r = 1;
	return r;
}

static double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}







