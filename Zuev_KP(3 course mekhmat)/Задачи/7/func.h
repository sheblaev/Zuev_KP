#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>

#define size 1000000

class Status
{
	public:
		int primes = 0;
};

class Args
{
	public:
		Status *s = nullptr;
		int n = 0;
		int m = 0;
		int p = 0;
		int res = 0;
		long long res0 = 0;
		double time = 0;
};

double get_cpu_time();

double get_full_time();

int prime(int n);

void reduce_sum(int p, long long *a);
