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
	int i, k = ar->m;
	double l = 0, result = 0;
	if ((ar->sm == 0) && (ar->em-ar->sm)>1)
	{
		s[k].element1 = ar->mas[ar->em-1];
		s[k].first1 = ar->mas[ar->em-2];
	}
	if ((ar->em == ar->n) && ((ar->em-ar->sm)>1))
	{
		s[k].element0 = ar->mas[ar->sm];
		s[k].second0 = ar->mas[ar->sm+1];
	}
	if ((ar->sm > 0) && (ar->em < ar->n))
	{
		s[k].element0 = ar->mas[ar->sm];
		s[k].second0 = ar->mas[ar->sm+1];
		s[k].element1 = ar->mas[ar->em-1];
		s[k].first1 = ar->mas[ar->em-2];
	}
	if (ar->em-ar->sm > 2)
	{
		for(i=ar->sm+1; i<ar->em-1; i++)
		{
			if ((ar->mas[i] > ar->mas[i-1]) && (ar->mas[i] > ar->mas[i+1]))
			{
				l=l+1;
				result = result+ar->mas[i];
			}
		}
	}
	ar->res = result;
	ar->res0 = l;
	reduce(ar->p, &(ar->res0), &(ar->res));
	for(i=0; i<ar->p-1; i++)
	{
		if (ar->n/ar->p != 1)
		{
			if (i>0)
			{
				if ((s[i].element0>s[i].second0) && (s[i].element0>s[i-1].element1))
				{
					ar->res = ar->res+s[i].element0;
					ar->res0 = ar->res0+1;
				}
			}
			if (i < ar->p-1)
			{
				if ((s[i].element1>s[i].first1) && (s[i].element1>s[i+1].element0))
				{
					ar->res = ar->res+s[i].element1;
					ar->res0 = ar->res0+1;
				}
			}
		}
	}
	for(i=1; i<ar->p-1; i++)
	{
		if (ar->n/ar->p == 1)
		{
			if ((s[i].element0>s[i].second0) && (s[i].element0>s[i-1].element1))
			{
				ar->res = ar->res+s[i].element0;
				ar->res0 = ar->res0+1;
			}
		}
	}
	i = ar->p-1;
	if (i>0)
	{
		if ((s[i].element0>s[i].second0) && (s[i].element0>s[i-1].element1))
		{
			ar->res = ar->res+s[i].element0;
			ar->res0 = ar->res0+1;
		}
	}
	for(i=ar->sm+1; i<ar->em-1; i++)
	{
		if ((ar->mas[i] > ar->mas[i-1]) && (ar->mas[i] > ar->mas[i+1]))
		{
			ar->mas[i] = (ar->res)/(ar->res0);
		}
	}
	for(i=0; i<ar->p; i++)
	{
		if (i>0)
		{
			if ((s[i].element0>s[i].second0) && (s[i].element0>s[i-1].element1))
			{
				ar->mas[i*(ar->n/ar->p)] = (ar->res)/(ar->res0);
			}
		}
		if (i < ar->p-1)
		{
			if ((s[i].element1>s[i].first1) && (s[i].element1>s[i+1].element0))
			{
				ar->mas[(i+1)*(ar->n/ar->p)-1] = (ar->res)/(ar->res0);
			}
		}
	}
	reduce_sum(ar->p, ar->mas, ar->n);
	return 0;
}

int main(int argc, char *argv[])
{
	int p = 0, n = 0, i = 0;
	double z = 0;
	pthread_t thread;
	if (!(argc == 4) || sscanf(argv[1], "%d", &p) != 1 || sscanf(argv[2], "%d", &n) != 1)
	{
		printf("Usage: %s p n  input", argv[0]);
		return 1;
	}
	p = atoi(argv[1]);
	n = atoi(argv[2]);
	Status *s = new Status[p+1];
	Args *a = new Args[p+1];
	double *mas = new double[n];
	FILE *f;
	f = fopen(argv[3], "r");
	if (f == nullptr)
	{
		return -1;
	}
	while(fscanf(f, "%lf", &z) == 1)
	{
		mas[i] = z;
		i = i+1;
	}
	if (!feof(f))
	{
		if (f != nullptr)
			fclose(f);
		return -2;
	}
	for(int j=0; j<p; j++)
	{
		a[j].mas = mas;
		a[j].m = j;
		a[j].n = n;
		a[j].p = p;
		a[j].sm = j*(n/p);
		if (j != p-1)
			a[j].em = (j+1)*(n/p);
		if ((n%p == 0) && (j == p-1))
			a[j].em = (j+1)*(n/p);
		if ((n%p != 0) && (j == p-1))
			a[j].em = n;
		a[j].res0 = 0;
		a[j].res = 0;
		a[j].s = s;
	}
	for(int j=1; j<p; j++)
	{
		pthread_create(&thread, NULL, kolvo, a+j);
	}
	kolvo(a);
	printf("Result p=%2d:", p);
	for(int j=0; j<n; j++)
	{
		printf("  %f", mas[j]);
	}
	printf("\n");
	if (f != nullptr)
		fclose(f);
	delete[] s;
	delete[] a;
	delete[] mas;
	return 0;
}
