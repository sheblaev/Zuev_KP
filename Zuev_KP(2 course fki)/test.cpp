#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include "func.h"
using namespace std;

static void *kolvo(void *a)
{
	Args *ap = (Args *)a;
	Status *s = ap->s;
	int k1 = 0, min = -1;
	vector<int> v0(ap->k);
	vector<int> i(ap->p);
	vector<int> v1(ap->k+ap->k);
	sort(ap->v.begin(), ap->v.end());
	for(int j=0; j<ap->k; j++)
	{
		v0[j] = ap->v[j];
	}
	s[ap->m].v0 = v0;
	for(int j=0; j<ap->p; j++)
	{
		if (ap->m == 0)
		{
			i[j]  = 1;
			if (j == 0)
			{
				i[j] = -1;
			}
		}
		else
		{
			i[j] = -1;
		}
	}
	s[ap->m].i = i;
	reduce_sum(ap->p);
	if (ap->m < ap->p-2)
	{
		while (k1 != ap->p-1-ap->m)
		{
			for(int j=ap->m+1; j<ap->p; j++)
			{
				if (s[ap->m].i[j] == 1)
				{
					min = j;
					break;
				}
			}
			if (min != -1)
			{
				for(int j=0; j<ap->k; j++)
				{
					ap->v[j] = s[ap->m].v0[j];
				}
				for(int j=0; j<ap->k; j++)
				{
					v1[j] = ap->v[j];
					v1[j+ap->k] = s[ap->m+k1+1].v0[j];
				}
				sort(v1.begin(), v1.end());
				for(int j=0; j<ap->k; j++)
				{
					ap->v[j] = v1[j];
					s[ap->m].v0[j] = v1[j];
					s[ap->m+k1+1].v0[j] = v1[j+ap->k];
				}
				k1 = k1+1;
				s[ap->m].i[ap->m+k1] = -1;
				if (k1 > 1)
				{
					s[ap->m+1].i[ap->m+k1] = 1;
				}
			}
			min = -1;
		}
	}
	reduce_sum(ap->p);
	if (ap->m == ap->p-2)
	{
		for(int j=0; j<ap->k; j++)
		{
			ap->v[j] = s[ap->m].v0[j];
		}
		for(int j=0; j<ap->k; j++)
		{
			v1[j] = ap->v[j];
			v1[j+ap->k] = s[ap->m+1].v0[j];
		}
		sort(v1.begin(), v1.end());
		for(int j=0; j<ap->k; j++)
		{
			ap->v[j] = v1[j];
			s[ap->m].v0[j] = v1[j];
			s[ap->m+1].v0[j] = v1[j+ap->k];
		}
	}
	reduce_sum(ap->p);
	if (ap->m == ap->p-1)
	{
		for(int j=0; j<ap->k; j++)
		{
			ap->v[j] = s[ap->m].v0[j];
		}
		sort(ap->v.begin(), ap->v.end());
	}
	reduce_sum(ap->p);
	return 0;
}

int main(int argc, char *argv[])
{
	int p = 0, n = 0, i = 0, i1 = 0, z = 0, k = 0, k1 = 0, l = 0;
	char *a1 = 0;
	pthread_t thread;
	if (!(argc == 3) || sscanf(argv[1], "%d", &p) != 1)
	{
		printf("Usage: %s p n input\n", argv[0]);
		return 1;
	}
	p = atoi(argv[1]);
	a1 = argv[2];
	FILE *f = fopen(a1, "rb");
	Status *s = new Status[p+1];
	Args *a = new Args[p+1];
	while (fread(&z, sizeof(int), 1, f) == 1)
	{
		n = n+1;
	}
	fclose(f);
	f = fopen(a1, "rb");
	k1 = n/p;
	if (k1>n-(k1)*(p-1))
	{
		k = n/p;
		l = n/p-(n-(k1)*(p-1));
	}
	else
	{
		k = n-(n/p)*(p-1);
		l = (k-k1)*(p-1);
	}
	for(int j=0; j<p; j++)
	{
		vector<int> v(k);
		for(i=0; i<k; i++)
		{
			v[i] = 0;
		}
		i = 0;
		//while (fscanf(f, "%d", &z) == 1)
		while (fread(&z, sizeof(int), 1, f) == 1)
		{
			if (j != p-1)
			{
				if (i1 < (j+1)*k1)
				{
					v[i] = z;
					i = i+1;
					i1 = i1+1;
					printf("%d ", z);
				}
				if (i1 >= (j+1)*k1)
				{
					i = 0;
					break;
				}
			}
			else
			{
				v[i] = z;
				i = i+1;
				printf("%d ", z);
			}
		}
		printf("\n");
		a[j].v = v;
		a[j].m = j;
		a[j].n = n;
		a[j].p = p;
		a[j].k = k;
		a[j].s = s;
	}
	for(int j=1; j<p; j++)
	{
		pthread_create(&thread, NULL, kolvo, a+j);
	}
	kolvo(a);
	//printf("\n");
	FILE *file;
	file = fopen("output.bin", "w");
	for(int j=0; j<p; j++)
	{
		for(i=0; i<k; i++)
		{
			if ((l != 0) && (a[j].v[i] == 0))
			{
				l = l-1;
			}
			else
			{
				//printf("%d ", a[j].v[i]);
				//fprintf(file, "%d ", a[j].v[i]);
				fwrite(&a[j].v[i], sizeof(int), 1, file);
			}
		}
		//printf("\n");
	}
	//printf("\n");
	fclose(f);
	fclose(file);
	delete[] s;
	delete[] a;
	return 0;
}
