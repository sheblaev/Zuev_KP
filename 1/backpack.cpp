#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "func.h"
using namespace std;

int backpack(int n, int k, int *w, int *v)
{
	int i, j, prev = 0, f = 0, max = 0;
	int **mas;
	mas = new int *[n+1];
	for (i = 0; i < n+1; i++)
	{
		mas[i] = new int [k+1];
	}
	for (i = 0; i < n+1; i++)
	{
		for (j = 0; j < k+1; j++)
		{
			mas[i][j] = 0;
		}
	}
	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= k; j++)
		{
			if ((i == 0) || (j == 0))
			{
				mas[i][j] = 0;
			}
			else
			{
				if (w[i - 1] > j)
				{
					mas[i][j] = mas[i - 1][j];
				}
				else
				{
					prev = mas[i - 1][j];
					f = v[i - 1]+mas[i - 1][j-w[i - 1]];
					if (prev > f)
					{
						mas[i][j] = prev;
					}
					else
					{
						mas[i][j] = f;
					}
				}
			}
		}
	}
	max = mas[n][k];
	for (i = 0; i < n+1; i++)
        {
                for (j = 0; j < k+1; j++)
                {
                        printf("%d ", mas[i][j]);
                }
		printf("\n");
        }
	printf("\n");
	for (i = 0; i < n+1; i++)
	{
		delete[] mas[i];
	}
	delete[] mas;
	return max;
}
