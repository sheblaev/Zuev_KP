#include <pthread.h> 
#include <cstdio>
#include <cstdlib>
#include "func.h"

void *kolvo(void *a)
{
	Args *ap = (Args *)a;
	Status *s;
	int n, p, m, i, j, c = 0, i1 = 0, primes = 0, max = 0, sum = 0, begin = 0, end = 0, count = 0;
	n = ap->n-1;
	p = ap->p;
	m = ap->m;
	s = ap->s;
	double t = get_cpu_time();
	for (j = 0; sum < n; j ++)
	{
		c = sum;
		count = 0;
		begin = j*size*p+size*m+3;
		end = begin+size;
		for (i = begin; i < end; i++)
		{
			if (prime(i) == 1)
			{
				count++;
			}
		}
		s[m].primes = count;
		reduce_sum(p, nullptr);
		for (i = 0; i < p; i ++)
		{
			sum = sum+s[i].primes;
		}
	}
	i1 = j-1;
	reduce_sum(p, nullptr);
	for (i = 0; i < p; i++)
	{
		if (c+s[i].primes >= n)
		{
			max = 0;
			primes = 0;
			begin =  i1*size*p+size*i+3;
			end = i1*size*p+size*i+3+size;
			for (j = begin; j < end; j++)
			{
				if (primes+c == n)
				{
					ap->res = max;
					break;
				}
				if (prime(j) == 1)
				{
					primes++;
					max = j;
				}
			}
			break;
		}
		c = c+s[i].primes;
	}
	reduce_sum(p, nullptr);
	if (m < p-1)
	{
		for (i = (m)*(ap->res/p); i < (m+1)*(ap->res/p); i++)
		{
			if (prime(i) == 1)
			{
				ap->res0 = ap->res0+i;
			}
		}
	}
	if (m == p-1)
	{
		ap->res0 = ap->res0+1;
		for (i = (m)*(ap->res/p); i < (ap->res+1); i++)
		{
			if (prime(i) == 1)
			{
				ap->res0 = ap->res0+i;
			}
		}
	}
	t = get_cpu_time()-t;
	ap->time = t;
	reduce_sum(p, &ap->res0);
	return 0;
}

int main (int argc, char * argv[])
{
	int p, n, i;
	pthread_t thread;
	if (!(argc == 3) || sscanf(argv[1], "%d", &p) != 1 || sscanf(argv[2], "%d", &n) != 1)
	{
		printf("Usage: %s p n", argv[0]);
		return 1;
	}
	p = atoi(argv[1]);
	n = atoi(argv[2]);
	Status *s = new Status[p];
	Args *a = new Args[p];
	for (i = 0; i < p; i ++)
	{
		a[i].s = s;
		a[i].n = n;
		a[i].m = i;
		a[i].p = p;
		a[i].res = 0;
		a[i].res0 = 0;
		a[i].time = 0;
	}
	double elapsed = get_full_time();
	for (i = 1; i < p; i++)
	{
		pthread_create (&thread, NULL, kolvo, a+i);
	}
	kolvo(a);
	elapsed = get_full_time()-elapsed;
	printf ("elapsed = %.2f\n", elapsed);
	printf ("Result = %lld\n", a[0].res0+1);
	for(i = 0; i < p; i++)
	{
		printf ("thread %d = %.2lf\n", i, a[i].time);
	}
	delete[] a;
	delete[] s;
	return 0;
}
