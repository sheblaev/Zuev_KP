#include <cstdio>
#include <pthread.h>

void reduce_sum(int p)
{
	static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;
	static pthread_cond_t c_out = PTHREAD_COND_INITIALIZER;
	static int t_in = 0;
	static int t_out = 0;
	static double *r = nullptr;
	int i;
	if (p <= 1) 
		return;
	pthread_mutex_lock(&m);
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
	t_out++;
	if (t_out >= p)
	{
		t_in = 0;
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

void reduce(int p, double *a)
{
        static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
        static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;
        static pthread_cond_t c_out = PTHREAD_COND_INITIALIZER;
        static int t_in = 0;
        static int t_out = 0;
        static double *r = nullptr;
        if (p <= 1)
                return;
        pthread_mutex_lock(&m);
        if(!r)
        {
                r = a;
        }
        else
        {
		if (*r > *a)
                        *r = *a;
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
        }
        t_out++;
        if (t_out >= p)
        {
                t_in = 0;
                r = nullptr;
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
