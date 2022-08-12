#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <pthread.h>
#include "func.h"
using namespace std;

static void *kolvo(void *a)
{
        Args *ar = (Args *)a;
	FILE *f1;
        f1 = fopen(ar->f, "r");
        int l = 0, k = 1, i = 0;
	double current = 0, pred = 0, pred1 = 0;
	if (f1 == NULL)
	{
		printf("Не удалось открыть файл\n");
		ar->error = -1;
		reduce_sum(ar->p);
		fclose(f1);
		return 0;
	}
	if ((fscanf(f1, "%lf", &current) != 1) && (!feof(f1)))
	{
		printf("Не удалось прочитать элемент\n");
		ar->error = -2;
		reduce_sum(ar->p);
		fclose(f1);
		return 0;
	}
	pred = current;
	while (fscanf(f1, "%lf", &current) == 1)
	{
		if ((pred1 < pred) && (pred1 < current) && (i > 0))
                {
                        l = l+1;
                }
		if (k == 1)
		{
			pred1 = pred;
			i = i+1;
			k = -1;
		}
		pred = current;
		k = k+1;
	}
	if (!feof(f1))
	{
		printf("Не удалось прочитать элемент\n");
                ar->error = -2;
                reduce_sum(ar->p);
                fclose(f1);
                return 0;
	}
        fclose(f1);
        ar->res = l;
        reduce_sum(ar->p);
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
                a[i].res = 0;
        }
        for(i=1; i<argc-1; i++)
        {
                pthread_create(&thread, NULL, kolvo, a+i);
        }
        kolvo(a);
        for(i=0; i<argc-1; i++)
        {
                result = result+a[i].res;
		e = e+a[i].error;
        }
	if (e == 0)
	{
        printf("%d\n", result);
	}
	else
	{
		printf("%d\n", e);
	}
        delete[] a;
        return 0;
}
