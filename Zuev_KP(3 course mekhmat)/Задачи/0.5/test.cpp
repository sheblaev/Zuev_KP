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
	Status *s = ar->s;
	FILE *f1;
	f1 = fopen(ar->f, "r");
	int l = 0, n = 0, q = 1, i = 0;
	double current = 0, pred = 0, pred1 = 0;
	int k = ar->m;
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
		s[k].first0 = pred;
		while (fscanf(f1, "%lf", &current) == 1)
		{
			if (i == 0)
			{
				s[k].second0 = current;
				i = i+1;
			}
			if ((current-pred)>5.0e-300)
			{
				n = n+1;
				pred1 = pred1+pred;
				q = 0;
			}
			else
			{
				if (q == 0)
				{
					n = n+1;
					pred1 = pred1+current;
					q = -1;
				}
			}
			pred = current;
		}
		if (!feof(f1))
		{
			ar->error = -2;
		}
		if (q == 0)
		{
			n = n+1;
			pred1 = pred1+current;
			q = -1;
		}
	}
	s[k].first1 = pred;
	s[k].second1 = current;
	if (i == 0)
		s[k].length = 1;
	else
		s[k].length = 0;
	ar->res = pred1;
	ar->res0 = n;
	if (f1 != nullptr)
		fclose(f1);
	reduce_sum(ar->p, &(ar->res0), &(ar->res));
	l = 0;
	f1 = fopen(ar->f, "r");
	i = 0;
        for(int j = 0; j < ar->p; j++)
        {
                i=i+s[j].length;
        }
        if (i == ar->p)
        {
                for(int j = 1; j < ar->p; j++)
                {
                        if ((s[j].first0-s[j-1].second1)>5.0e-300)
                        {
                                if((((s[j-1].first1-s[j-1].second1)>5.0e-300) || (fabs(s[j-1].first1-s[j-1].second1)<5.0e-300)) && (((s[j].first0-s[j].second0)>5.0e-300) || (fabs(s[j].first0-s[j].second0)<5.0e-300)))
                                {
                                        ar->res0=ar->res0+2;
                                        ar->res=ar->res+s[j-1].second1;
                                        ar->res=ar->res+s[j].first0;
                                }
                                if(((s[j-1].second1-s[j-1].first1)>5.0e-300) && (((s[j].first0-s[j].second0)>5.0e-300) || (fabs(s[j].first0-s[j].second0)<5.0e-300)))
                                {
                                        ar->res0=ar->res0+1;
                                        ar->res=ar->res+s[j].first0;
                                }
                                if((((s[j-1].first1-s[j-1].second1)>5.0e-300) || (fabs(s[j-1].first1-s[j-1].second1)<5.0e-300)) && ((s[j].second0-s[j].first0)>5.0e-300))
                                {
                                        ar->res0=ar->res0+1;
                                        ar->res=ar->res+s[j-1].second1;
                                }
                        }
                }
        }
	else
        {
                for(int j = 1; j < ar->p; j++)
                {
                        if ((s[j].first0-s[j-1].second1)>5.0e-300)
                        {
                                ar->res0=ar->res0+1;
                                ar->res=ar->res+s[j-1].second1;
                        }
                }
		if (ar->p > 1)
		{
                	if ((s[(ar->p)-1].first0-s[(ar->p)-2].second1)>5.0e-300)
			{
				ar->res0=ar->res0+1;
                        	ar->res=ar->res+s[(ar->p)-1].first0;
			}
		}
        }
	if (f1 == nullptr)
	{
		ar->error = -1;
	}
	if (ar->error == 0)
	{
		while (fscanf(f1, "%lf", &current) == 1)
			if (current < ((ar->res)/(ar->res0)))
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
	Status *s = new Status[argc];
	Args *a = new Args[argc];
	for(i=0; i<argc-1; i++)
	{
		a[i].f = argv[i+1];
		a[i].c = 1;
		a[i].m = i;
		a[i].error = 0;
		a[i].p = argc-1;
		a[i].res0 = 0;
		a[i].res = 0;
		a[i].res1 = 0;
		a[i].s = s;
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
	delete[] s;
	delete[] a;
	return 0;
}
