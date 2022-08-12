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
	int i, k = ar->m, j = 0, z = 0;
	double pred0 = 0, pred1 = 0, q = 0;
	if (ar->n >= 5)
	{
		if (ar->em-ar->sm == 1)
                {
                        s[k].element0 = ar->mas[ar->sm];
                        s[k].element1 = ar->mas[ar->em-1];
			if (ar->em < ar->n)
                        	s[k].first0 = ar->mas[ar->em];
			if (ar->em < ar->n-1)
                        	s[k].second0 = ar->mas[ar->em+1];
			if (ar->sm > 1)
                        	s[k].first1 = ar->mas[ar->sm-2];
			if (ar->sm > 0)
                        	s[k].second1 = ar->mas[ar->sm-1];
                }
		if (ar->em-ar->sm == 2)
		{
			s[k].element0 = ar->mas[ar->sm];
			s[k].element1 = ar->mas[ar->em-1];
			s[k].first0 = ar->mas[ar->em-1];
			s[k].second1 = ar->mas[ar->sm];
			if (ar->em < ar->n)
				s[k].second0 = ar->mas[ar->em];
			if (ar->sm > 0)
				s[k].first1 = ar->mas[ar->sm-1];
		}
		for(i=ar->sm; i<ar->em; i++)
		{
			if ((ar->em-ar->sm > 2) && (i > ar->sm) && (i < ar->em-1))
			{
				if (j == 0)
				{
					s[k].element0 = ar->mas[ar->sm];
					s[k].element1 = ar->mas[ar->em-1];
					s[k].first0 = ar->mas[ar->sm+1];
					s[k].second0 = ar->mas[ar->sm+2];
					s[k].first1 = ar->mas[ar->em-3];
					s[k].second1 = ar->mas[ar->em-2];
					j = j+1;
				}
				if ((i != 0) && (i != 1) && (i != ar->n-2) && (i != ar->n-1))
				{
					if ((i == 2) || (i == ar->sm+1))
					{
						pred0 = ar->mas[i-2];
						pred1 = ar->mas[i-1];
					}
					if ((pred0*pred1*ar->mas[i+1]*ar->mas[i+2]) > 5.0e-300)
					{
						q = ar->mas[i];
						ar->mas[i] = pow(pred0*pred1*ar->mas[i+1]*ar->mas[i+2],1/4.0);
						pred0 = pred1;
						pred1 = q;
						z = 1;
					}
					if (fabs(pred0*pred1*ar->mas[i+1]*ar->mas[i+2]) < 5.0e-300)
					{
						q = ar->mas[i];
						ar->mas[i] = 0;
						pred0 = pred1;
						pred1 = q;
						z = 1;
					}
					if (((pred0*pred1*ar->mas[i+1]*ar->mas[i+2]) < -5.0e-300) && (z == 0))
                                        {
                                                q = ar->mas[i];
                                                pred0 = pred1;
                                                pred1 = q;
                                        }
					z = 0;
				}
			}
		}
	}
	reduce_sum(ar->p, ar->mas, ar->n);
	if (ar->n >= 5)
	{
	if (ar->n/ar->p == 1)
	{
		if (ar->n-(ar->p-1)*(ar->n/ar->p) > 2)
		{
			for (i=2; i<ar->p; i++)
			{
				if ((s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0) > 5.0e-300)
				{
					ar->mas[i] = pow(s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0,1/4.0);
				}
				if (fabs(s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0) < 5.0e-300)
				{
					ar->mas[i] = 0;
				}
			}
		}
		if (ar->n-(ar->p-1)*(ar->n/ar->p) == 2)
		{
			for (i=2; i<ar->p-1; i++)
                        {
                                if ((s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0) > 5.0e-300)
                                {
                                        ar->mas[i] = pow(s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0,1/4.0);
                                }
                                if (fabs(s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0) < 5.0e-300)
                                {
                                        ar->mas[i] = 0;
                                }
                        }
		}
		if (ar->n-(ar->p-1)*(ar->n/ar->p) == 1)
		{
			for (i=2; i<ar->p-2; i++)
                        {
                                if ((s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0) > 5.0e-300)
                                {
                                        ar->mas[i] = pow(s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0,1/4.0);
                                }
                                if (fabs(s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0) < 5.0e-300)
                                {
                                        ar->mas[i] = 0;
                                }
                        }
		}
	}
	else
	{
		for (i=0; i<ar->p; i++)
		{
			if (i != 0)
			{
				if (i == ar->p-1)
				{
					if (ar->n-(ar->p-1)*(ar->n/ar->p)>2)
					{
						if ((s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0) > 5.0e-300)
						{
							ar->mas[i*(ar->n/ar->p)] = pow(s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0,1/4.0);
						}
						if (fabs(s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0) < 5.0e-300)
						{
							ar->mas[i*(ar->n/ar->p)] = 0;
						}
					}
				}
					else
					{
						if ((s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0) > 5.0e-300)
						{
							ar->mas[i*(ar->n/ar->p)] = pow(s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0,1/4.0);
						}
						if (fabs(s[i-1].second1*s[i-1].element1*s[i].first0*s[i].second0) < 5.0e-300)
						{
							ar->mas[i*(ar->n/ar->p)] = 0;
						}
					}
			}
			if (i != ar->p-1)
			{
				if (i == 0)
				{
					if ((ar->n/ar->p)>2)
					{
						if ((s[i+1].first0*s[i+1].element0*s[i].first1*s[i].second1) > 5.0e-300)
						{
							ar->mas[(i+1)*(ar->n/ar->p)-1] = pow(s[i+1].first0*s[i+1].element0*s[i].first1*s[i].second1,1/4.0);
						}
						if (fabs(s[i+1].first0*s[i+1].element0*s[i].first1*s[i].second1) < 5.0e-300)
						{
							ar->mas[(i+1)*(ar->n/ar->p)-1] = 0;
						}
					}
				}
				else
				{
					if ((s[i+1].first0*s[i+1].element0*s[i].first1*s[i].second1) > 5.0e-300)
					{
						ar->mas[(i+1)*(ar->n/ar->p)-1] = pow(s[i+1].first0*s[i+1].element0*s[i].first1*s[i].second1,1/4.0);
					}
					if (fabs(s[i+1].first0*s[i+1].element0*s[i].first1*s[i].second1) < 5.0e-300)
					{
						ar->mas[(i+1)*(ar->n/ar->p)-1] = 0;
					}
				}
			}
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
