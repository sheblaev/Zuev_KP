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
	int i, j, h, k = ar->m;
	double q = 0;
	double *f1 = new double[ar->n2];
	double *s0 = new double[ar->n2];
	double *e0 = new double[ar->n2];
	double *e1 = new double[ar->n2];
	double *z = new double[ar->n2];
	double *pred = new double[ar->n2];
	if ((ar->sm == 0) && ((ar->em-ar->sm) > 1))
	{
		for(j=0; j<ar->n2; j++)
		{
			e1[j] = ar->mas[(ar->em-1)*ar->n2+j];
			f1[j] = ar->mas[(ar->em-2)*ar->n2+j];
		}
		s[k].first1 = f1;
		s[k].element1 = e1;
	}
	if ((ar->em == ar->n1) && ((ar->em-ar->sm) > 1))
	{
		for(j=0; j<ar->n2; j++)
		{
			e0[j] = ar->mas[ar->sm*ar->n2+j];
			s0[j] = ar->mas[(ar->sm+1)*ar->n2+j];
		}
		s[k].second0 = s0;
		s[k].element0 = e0;
	}
	if ((ar->sm > 0) && (ar->em < ar->n1))
	{
		for(j=0; j<ar->n2; j++)
		{
			e0[j] = ar->mas[ar->sm*ar->n2+j];
			e1[j] = ar->mas[(ar->em-1)*ar->n2+j];
			s0[j] = ar->mas[(ar->sm+1)*ar->n2+j];
			f1[j] = ar->mas[(ar->em-2)*ar->n2+j];
		}
		s[k].first1 = f1;
		s[k].second0 = s0;
		s[k].element0 = e0;
		s[k].element1 = e1;
	}
	if ((ar->em-ar->sm) == 1)
	{
		for(j=0; j<ar->n2; j++)
                {
                        e0[j] = ar->mas[ar->sm*ar->n2+j];
                }
                s[k].element0 = e0;
	}
	ar->res = ar->mas[ar->sm*ar->n2];
	for(i=ar->sm; i<ar->em; i++)
	{
		for(j=0; j<ar->n2; j++)
		{
			if (ar->res >= ar->mas[i*ar->n2+j])
			{
				ar->res = ar->mas[i*ar->n2+j];
			}
		}
	}
	reduce(ar->p, &(ar->res));
	if (ar->em-ar->sm > 2)
	{
		for(h=0; h<ar->n2; h++)
		{
			z[h] = ar->mas[ar->sm*ar->n2+h];
		}
		for(i=ar->sm+1; i<ar->em-1; i++)
		{
			q = ar->mas[i*ar->n2];
			for(h=0; h<ar->n2; h++)
                        {
				pred[h] = ar->mas[i*ar->n2+h];
                        }
			for(j=1; j<ar->n2-1; j++)
			{
				if ((ar->mas[i*ar->n2+j] < ar->mas[i*ar->n2+j+1]) && (ar->mas[i*ar->n2+j] < q) && (ar->mas[i*ar->n2+j] < z[j]) && (ar->mas[i*ar->n2+j] < ar->mas[(i+1)*ar->n2+j]))
				{
					q = ar->mas[i*ar->n2+j];
					ar->mas[i*ar->n2+j] = ar->res;
				}
				else
				{
					q = ar->mas[i*ar->n2+j];
				}
			}
			for(h=0; h<ar->n2; h++)
                        {
				z[h] = pred[h];
			}
		}
	}
	reduce_sum(ar->p);
	if (ar->p > 1)
	{
		for(i=0; i<ar->p; i++)
		{
			if ((ar->n1/ar->p) > 1)
			{
				if (i == 0)
				{
					q = s[i].element1[0];
					for(j=1; j<ar->n2-1; j++)
					{
						if ((s[i].element1[j] < s[i].first1[j]) && (s[i].element1[j] < s[i+1].element0[j]) && (s[i].element1[j] < s[i].element1[j+1]) && (s[i].element1[j] < q))
						{
							ar->mas[((i+1)*(ar->n1/ar->p)-1)*ar->n2+j] = ar->res;
						}
						q = s[i].element1[j];
					}
				}
				if ((i == ar->p-1) && ((ar->n1-(ar->p-1)*(ar->n1/ar->p))>1))
				{
					q = s[i].element0[0];
					for(j=1; j<ar->n2-1; j++)
					{

						if ((s[i].element0[j] < s[i].second0[j]) && (s[i].element0[j] < s[i-1].element1[j]) && (s[i].element0[j] < s[i].element0[j+1]) && (s[i].element0[j] < q))
						{
							ar->mas[i*(ar->n1/ar->p)*ar->n2+j] = ar->res;
						}
						q = s[i].element0[j];
					}
				}
				if ((i != 0) && (i != ar->p-1))
				{
					q = s[i].element1[0];
					for(j=1; j<ar->n2-1; j++)
					{
						if ((s[i].element1[j] < s[i].first1[j]) && (s[i].element1[j] < s[i+1].element0[j]) && (s[i].element1[j] < s[i].element1[j+1]) && (s[i].element1[j] < q))
						{
							ar->mas[((i+1)*(ar->n1/ar->p)-1)*ar->n2+j] = ar->res;
						}
						q = s[i].element1[j];
					}
					q = s[i].element0[0];
					for(j=1; j<ar->n2-1; j++)
                                        {
						if ((s[i].element0[j] < s[i].second0[j]) && (s[i].element0[j] < s[i-1].element1[j]) && (s[i].element0[j] < s[i].element0[j+1]) && (s[i].element0[j] < q))
						{
							ar->mas[i*(ar->n1/ar->p)*ar->n2+j] = ar->res;
						}
						q = s[i].element0[j];
					}
				}
			}
			if ((ar->n1/ar->p) == 1)
			{
				if ((i == ar->p-1) && ((ar->n1-(ar->p-1)*(ar->n1/ar->p))>1))
                                {
                                        q = s[i].element0[0];
                                        for(j=1; j<ar->n2-1; j++)
                                        {
                                                if ((s[i].element0[j] < s[i].second0[j]) && (s[i].element0[j] < s[i-1].element0[j]) && (s[i].element0[j] < s[i].element0[j+1]) && (s[i].element0[j] < q))
                                                {
                                                        ar->mas[i*(ar->n1/ar->p)*ar->n2+j] = ar->res;
                                                }
						q = s[i].element0[j];
                                        }
                                }
				if ((i != 0) && (i != ar->p-1))
                                {
                                        q = s[i].element0[0];
                                        for(j=1; j<ar->n2-1; j++)
                                        {
                                                if ((s[i].element0[j] < s[i+1].element0[j]) && (s[i].element0[j] < s[i-1].element0[j]) && (s[i].element0[j] < s[i].element0[j+1]) && (s[i].element0[j] < q))
                                                {
                                                        ar->mas[i*(ar->n1/ar->p)*ar->n2+j] = ar->res;
                                                }
						q = s[i].element0[j];
                                        }
                                }
			}
		}
	}
	reduce_sum(ar->p);
	delete[] f1;
	delete[] s0;
	delete[] e0;
	delete[] e1;
	delete[] z;
	delete[] pred;
	return 0;
}

int main(int argc, char *argv[])
{
	int p = 0, n1 = 0, n2 = 0, i = 0;
	double z = 0;
	pthread_t thread;
	if (!(argc == 5) || sscanf(argv[1], "%d", &p) != 1 || sscanf(argv[2], "%d", &n1) != 1 || sscanf(argv[3], "%d", &n2) != 1)
	{
		printf("Usage: %s p n1 n2 input\n", argv[0]);
		return 1;
	}
	p = atoi(argv[1]);
	n1 = atoi(argv[2]);
	n2 = atoi(argv[3]);
	Status *s = new Status[p+1];
	Args *a = new Args[p+1];
	double *mas = new double[n1*n2];
	FILE *f;
	f = fopen(argv[4], "r");
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
		a[j].n1 = n1;
		a[j].n2 = n2;
		a[j].p = p;
		a[j].sm = j*(n1/p);
		if (j != p-1)
			a[j].em = (j+1)*(n1/p);
		if ((n1%p == 0) && (j == p-1))
			a[j].em = (j+1)*(n1/p);
		if ((n1%p != 0) && (j == p-1))
			a[j].em = n1;
		a[j].res = 0;
		a[j].s = s;
	}
	for(int j=1; j<p; j++)
	{
		pthread_create(&thread, NULL, kolvo, a+j);
	}
	kolvo(a);
	printf("Result p=%2d:\n", p);
	for(int k=0; k<n1; k++)
	{
		for(int j=0; j<n2; j++)
		{
			printf("  %.3e", mas[k*n2+j]);
		}
		printf("\n");
	}
	printf("\n");
	if (f != nullptr)
		fclose(f);
	delete[] s;
	delete[] a;
	delete[] mas;
	return 0;
}
