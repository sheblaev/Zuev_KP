#include <cstdio>
#include <pthread.h>

void reduce_sum(int p, int *a, double *b)
{
	static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;
	static pthread_cond_t c_out = PTHREAD_COND_INITIALIZER;
	static int t_in = 0;
	static int t_out = 0;
	static int *r = nullptr;
	static double *r1 = nullptr;
	if (p <= 1) 
		return;
	pthread_mutex_lock(&m);
	if(!r)
	{
		r = a;
                r1 = b;
	}
	else
	{
		if ((*a < *r) && (*a != 0))
		{
			*r = *a;
			*r1 = *b;
		}
		if ((*r == 0) && (*a != 0))
		{
			*r=*r+*a;
			*r1=*r1+*a;
		}
	}
	t_in++;
	if (t_in >= p)
	{
		t_out = 0;
		pthread_cond_broadcast(&c_in);
	}
	else
	{
		while (t_in < p)
		{
			pthread_cond_wait(&c_in, &m);
		}
	}
	if (r != a)
	{
		*a = *r;
		*b = *r1;
	}
	t_out++;
	if (t_out >= p)
	{
		t_in = 0;
		r = nullptr;
		r1 = nullptr;
		pthread_cond_broadcast(&c_out);
	}
	else
	{
		while (t_out < p)
		{
			pthread_cond_wait(&c_out, &m);
		}
	}
	pthread_mutex_unlock(&m);
}

