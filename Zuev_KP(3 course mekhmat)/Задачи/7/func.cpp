#include <thread>
#include <cstring>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "func.h"

double get_cpu_time()
{
	struct rusage buf;
	getrusage(RUSAGE_THREAD, &buf);
	return buf.ru_utime.tv_sec + buf.ru_utime.tv_usec/1.e+6;
}

double get_full_time()
{
	struct timeval buf;
	gettimeofday (&buf, 0);
	return buf.tv_sec + buf.tv_usec/1.e+6;
}

int prime(int n)
{
	int i;
	if(n == 1)
	{
		return 0;
	}
	if (n%2 == 0)
	{
		return 0;
	}
	for(i = 3; i*i <= n; i = i+2)
	{
		if(n%i == 0)
		{
			return 0;
		}
	}
	return 1;
}

void reduce_sum(int p, long long *a)
{
	static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;
	static pthread_cond_t c_out = PTHREAD_COND_INITIALIZER;
	static int t_in = 0;
	static int t_out = 0;
	static long long *r = nullptr;
	if (p <= 1)
		return;
	pthread_mutex_lock(&m);
	if(!r)
	{
		r = a;
	}
	else
	{
		*r=*r+*a;
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
