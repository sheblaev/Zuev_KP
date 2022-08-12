#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <pthread.h>
#include <cmath>
#include "func.h"
using namespace std;

static void *kolvo(void *a)
{
	Args *ar = (Args *)a;
	FILE *f1;
	f1 = fopen(ar->f, "r");
	int l = 0, n = 0, q = 1;
	double current = 0, pred = 0, pred1 = 0;
	if (f1 == nullptr)
	{
		ar->error = -1;
	}
	if (ar->error == 0)
	{
		if ((fscanf(f1, "%lf", &current) != 1) && (!feof(f1)))
		{
			ar->error = -2;
		}
		pred = current;
		while (fscanf(f1, "%lf", &current) == 1)
		{
			if (fabs(pred-current)<1.4e-45)
			{
				l=l+1;
			}
			else
			{
				q = 0;
			}
			if (q == 0)
			{
				q=1;
				if (((l < n) || (n == 0)) && (l != 0))
				{
					n = l;
					pred1 = pred;
				}
				if ((l == n) && (l != 0) && (pred < pred1))
				{
					n = l;
					pred1 = pred;
				}
				l=0;
			}
			pred = current;
		}
		if (!feof(f1))
		{
			ar->error = -2;
		}
		if (((l < n) || (n == 0)) && (l != 0))
		{
			n = l;
			pred1 = pred;
		}
		if ((l == n) && (l != 0) && (pred < pred1))
		{
			n = l;
			pred1 = pred;
		}
	}
	ar->res = pred1;
	ar->res0 = n;
	if (f1 != nullptr)
		fclose(f1);
	reduce_sum(ar->p, &(ar->res0), &(ar->res));
	l = 0;
	f1 = fopen(ar->f, "r");
	if (f1 == nullptr)
	{
		ar->error = -1;
	}
	if (ar->error == 0)
	{
		while (fscanf(f1, "%lf", &current) == 1)
			if (current < ar->res)
				l=l+1;
		if (!feof(f1))
		{
			ar->error = -2;
		}
		ar->res1 = l;
	}
	if (f1 != nullptr)
		fclose(f1);
	reduce_sum(ar->p, nullptr, nullptr);
	return 0;
}

int main(int argc, char *argv[])
{
	int result = 0, i, e;
	e = 0;
	pthread_t thread;
	if((argc-1) == 0)
	{
		printf("Нет файлов\n");
		return 0;
	}
	Args *a = new Args[argc];
	for(i=0; i<argc-1; i++)
	{
		a[i].f = argv[i+1];
		a[i].m = i;
		a[i].error = 0;
		a[i].p = argc-1;
		a[i].res0 = 0;
		a[i].res = 0;
		a[i].res1 = 0;
	}
	for(i=1; i<argc-1; i++)
	{
		pthread_create(&thread, NULL, kolvo, a+i);
	}
	kolvo(a);
	for(i=0; i<argc-1; i++)
	{
		result = result+a[i].res1;
		e = e+a[i].error;
	}
	if (e == 0)
	{
		printf("%d\n", result);
	}
	else
	{
		if (e == -1)
		{
			printf("Не удалось открыть файл\n");
			printf("%d\n", e);
		}
		if (e == -2)
		{
			printf("Не удалось прочитать элемент\n");
			printf("%d\n", e);
		}
	}
	delete[] a;
	return 0;
}
