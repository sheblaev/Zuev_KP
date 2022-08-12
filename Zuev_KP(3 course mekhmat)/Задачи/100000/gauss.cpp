#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <cmath>
#include "func.h"
using namespace std;
void reduce_sum(int p);
void reduce(int p, int *a, double *b);
void getblock(double *A, double *C, int n, int r0, int r1, int i, int j);
void setblock(double *A, double *C, int n, int r0, int r1, int i, int j);
double *umnoz(double *b, double *c, double *d, int r0, int c0, int c1);
double *obrat(int N, double *matrix, double *matrixinv);
void swaprows(double *matrix, int row1, int row2, int N);
void plusrows(double *matrix, int N, int row1, int row2, double k);
void multrow(double *matrix, int N, int row, double k);

static void *solution(void *a1)
{
	Args *ar = (Args *)a1;
	int a, k0, i = 0, i1, j, h, l, k1, t0 = 0, t = 0;
	int n = ar->n, m = ar->m, k = ar->k, p = ar->p, q = ar->q, q1 = 0, l1 = 0;
	double z1 = 0, sum = 0, q_ = 0;
	k0 = n/m;
	k1 = k0;
	l = n-m*k0;
	if (l == 0)
	{
		k1 = k0-1;
	}
	double *cm = new double[m*m];
	double *dm = new double[m*m];
	double *cl = new double[m*l];
	double *dl = new double[m*l];
	double *ob = new double[l*l];
	double *o = new double[l*l];
	double *b0 = new double[m];
	double *b1 = new double[l];
	double *omasn = new double[n*n];
	double *omas = new double[m*m];
	double *c = new double[m*m];
	cpu_set_t cpu;
	CPU_ZERO (&cpu);
	int n_cpus = get_nprocs();
	int cpu_id = n_cpus-1-(k%n_cpus);
	CPU_SET (cpu_id, &cpu);
	pthread_t tid = pthread_self();
	pthread_setaffinity_np (tid, sizeof(cpu), &cpu);
	q1 = n*n;
	if (p != 1)
	{
		if (q == 0)
		{
			if (ar->s1 == 0)
			{
				if (k == 0)
				{
					FILE *f;
					f = fopen(ar->filename, "r");
					while(fscanf(f, "%lf", &z1) == 1)
					{
						l1 = l1+1;
					}
					fclose(f);
					if (l1==q1)
					{
						f = fopen(ar->filename, "r");
						while (fscanf(f, "%lf", &z1) == 1)
						{
							ar->mas[i] = z1;
							i = i+1;
						}
						fclose(f);
					}
					else
					{
						for ( i = 0; i < n*n; i++)
						{
							ar->mas[i] = 0;
						}
					}
					for(i = 0; i < n; i++)
					{
						ar->b[i] = 0;
						for(j = 0; j < (n+1)/2; j++)
						{
							ar->b[i] = ar->b[i]+ar->mas[n*i+(2*j)];
						}
					}
					for(i = 0; i < n; i++)
					{
						ar->b5[i] = ar->b[i];
						for(j = 0; j < n; j++)
						{
							ar->mas5[i*n+j] = ar->mas[i*n+j];
						}
					}
				}
			}
			else
			{
				for (i = k*m; i < n; i+=p*m)
				{
					h = (i+m < n ? i+m : n);
					for (i1 = i; i1 < h; i1++)
					{
						for (j = 0; j < n; j++)
						{
							ar->mas[i1*n+j] = func(ar->s1, n, i1, j);
							ar->mas5[i1*n+j] = func(ar->s1, n, i1, j);
						}
					}
				}
				for (i = k*m; i < n; i+=p*m)
				{
					h = (i+m < n ? i+m : n);
					for (i1 = i; i1 < h; i1++)
					{
						ar->b[i1] = 0;
						ar->b5[i1] = 0;
						for(j = 0; j < (n+1)/2; j++)
						{
							ar->b[i1] = ar->b[i1]+ar->mas[n*i1+(2*j)];
							ar->b5[i1] = ar->b5[i1]+ar->mas5[n*i1+(2*j)];
						}
					}
				}
			}
		}
		reduce_sum(ar->p);
	}
	if ((q == 0) && (k == 0))
	{
		if (ar->r < n)
		{
			for (int z = 0; z < ar->r; z++)
			{
				for (int s = 0; s < ar->r; s++)
				{
					printf("%10.3e", ar->mas[z*n+s]);
				}
				printf("\n");
			}
			for (int s = 0; s < ar->r; s++)
			{
				printf("%10.3e\n", ar->b[s]);
			}
			printf("\n");
		}
		else
		{
			for (int z = 0; z < n; z++)
			{
				for (int s = 0; s < n; s++)
				{
					printf("%10.3e", ar->mas[z*n+s]);
				}
				printf("\n");
			}
			for (int s = 0; s < n; s++)
			{
				printf("%10.3e\n", ar->b[s]);
			}
			printf("\n");
		}
	}
	if (n <= 14)
	{
		for(i = 0; i < n*n; i++)
		{
			q_=q_+modul(ar->mas[i]);
		}
		if ((modul(q_) <= 5.0e-300) && (n != 1))
		{
			ar->error = -1;
			delete[] omasn;
			delete[] cm;
			delete[] dm;
			delete[] cl;
			delete[] dl;
			delete[] ob;
			delete[] o;
			delete[] b0;
			delete[] b1;
			delete[] omas;
			delete[] c;
			return 0;
		}
		omasn = obrat(n, ar->mas, omasn);
		for (int z = 0; z < n; z++)
		{
			for (int s = 0; s < n; s++)
			{
				if (modul(omasn[n*z+s]) >= 5.0e-300)
				{
					t = t+1;
				}
			}
		}
		if ((t == 0) && (n != 1))
		{
			ar->error = -5;
			delete[] omasn;
			delete[] cm;
			delete[] dm;
			delete[] cl;
			delete[] dl;
			delete[] ob;
			delete[] o;
			delete[] b0;
			delete[] b1;
			delete[] omas;
			delete[] c;
			return 0;
		}
	}
	t = 0;
	for(j=0; j<n*m; j++)
	{
		ar->stroka[j] = ar->mas[n*m*q+j];
	}
	if (m != 1)
	{
		for (h = 0; h < k0; h++)
		{
			j=k+h*p;
			if ((j >= q) && (j < k0))
			{
				getblock(ar->stroka, c, n, m, m, 0, j);
				obrat(m, c, omas);
				for (i = 0; i < m; i++)
				{
					for (int z = 0; z < m; z++)
					{
						sum = sum+modul(omas[i*m+z]);
					}
				}
				if (((ar->min >= sum) || (ar->min <= 5.0e-300)) && (sum >= 5.0e-300))
				{
					ar->min = sum;
					ar->otvet = j;
				}
				sum = 0;
			}
		}
	}
	else
	{
		if (modul(ar->mas[n*q+q]) <= 5.0e-300)
		{
			ar->min = 0;
			for (h = 0; h < k0; h++)
			{
				i=k+h*p;
				if ((i >= 0) && (i < n))
				{
					sum = modul(ar->stroka[i]);
					if (((ar->min >= sum) || (ar->min <= 5.0e-300)) && (sum >= 5.0e-300))
					{
						ar->min = sum;
						ar->otvet = i;
					}
					sum = 0;
				}
			}
		}
		else
		{
			ar->otvet = q;
			ar->min = 1;
		}
	}
	reduce(ar->p, &ar->otvet, &ar->min);
	if (m == 1)
	{
		for (h = 0; h < k0; h++)
		{
			j=k+h*p;
			if ((j >= q) && (j < k0))
			{
				getblock(ar->mas, cm, n, m, m, j, ar->otvet);
				getblock(ar->mas, dm, n, m, m, j, q);
				setblock(ar->mas, cm, n, m, m, j, q);
				setblock(ar->mas, dm, n, m, m, j, ar->otvet);
			}
		}
		if (k == 0)
		{
			for (int z = q*m; z < q*m+m; z++)
			{
				t = ar->nomer[z];
				ar->nomer[z] = ar->nomer[z+ar->otvet*m-q*m];
				ar->nomer[z+ar->otvet*m-q*m] = t;
			}
		}
	}
	else
	{
		for (h = 0; h < k0; h++)
		{
			j=k+h*p;
			if ((j >= q) && (j < k0))
			{
				getblock(ar->mas, cm, n, m, m, j, ar->otvet);
				getblock(ar->mas, dm, n, m, m, j, q);
				setblock(ar->mas, cm, n, m, m, j, q);
				setblock(ar->mas, dm, n, m, m, j, ar->otvet);
			}
			if ((l != 0) && (j == q))
			{
				getblock(ar->mas, cl, n, l, m, k0, ar->otvet);
				getblock(ar->mas, dl, n, l, m, k0, q);
				setblock(ar->mas, cl, n, l, m, k0, q);
				setblock(ar->mas, dl, n, l, m, k0, ar->otvet);
			}
		}
		if (k == 0)
		{
			for (int z = q*m; z < q*m+m; z++)
			{
				t = ar->nomer[z];
				ar->nomer[z] = ar->nomer[z+ar->otvet*m-q*m];
				ar->nomer[z+ar->otvet*m-q*m] = t;
			}
		}
	}
	reduce_sum(ar->p);
	getblock(ar->stroka, cm, n, m, m, 0, ar->otvet);
	omas = obrat(m, cm, omas);
	for (h = 0; h < k0; h++)
	{
		j=k+h*p;
		if ((j >= q) && (j<k0))
		{
			getblock(ar->mas, cm, n, m, m, q, j);
			cm = umnoz(cm, omas, cm, m, m, m);
			setblock(ar->mas, cm, n, m, m, q, j);
		}
		if (j == q)
		{
			if (l != 0)
			{
				getblock(ar->mas, cl, n, m, l, q, k0);
				cl = umnoz(cl, omas, cl, m, m, l);
				setblock(ar->mas, cl, n, m, l, q, k0);
			}
			for (i = 0; i < m; i++)
			{
				b0[i] = ar->b[i+q*m];
			}
			b0 = umnoz(b0, omas, b0, m, m, 1);
			for (i = 0; i < m; i++)
			{
				ar->b[i+q*m] = b0[i];
			}
		}
	}
	reduce_sum(ar->p);
	for (h = 0; h <= k0; h++)
	{
		i = k+h*p;
		if ((i > q) && (i < k0))
		{
			getblock(ar->mas, dm, n, m, m, i, q);
			for (int s = 0; s < m; s++)
			{
				b0[s] = ar->b[s+q*m];
			}
			b0 = umnoz(b0, dm, b0, m, m, 1);
			for (int s = 0; s < m; s++)
			{
				ar->b[s+i*m] = ar->b[s+i*m]-b0[s];
			}
			for (j = k1; j >= q; j--)
			{
				if (j == k0)
				{
					getblock(ar->mas, dm, n, m, m, i, q);
					getblock(ar->mas, cl, n, m, l, q, j);
					cl = umnoz(cl, dm, cl, m, m, l);
					getblock(ar->mas, dl, n, m, l, i, j);
					for (int s=0; s<m; s++)
					{
						for (int z=0; z<l; z++)
						{
							dl[l*s+z]=dl[l*s+z]-cl[l*s+z];
						}
					}
					setblock(ar->mas, dl, n, m, l, i, j);
				}
				else
				{
					getblock(ar->mas, dm, n, m, m, i, q);
					getblock(ar->mas, cm, n, m, m, q, j);
					cm = umnoz(cm, dm, cm, m, m, m);
					getblock(ar->mas, dm, n, m, m, i, j);
					for (int s=0; s<m; s++)
					{
						for (int z=0; z<m; z++)
						{
							dm[m*s+z]=dm[m*s+z]-cm[m*s+z];
						}
					}
					setblock(ar->mas, dm, n, m, m, i, j);
				}
			}
		}
		if ((l != 0) && (i == k0))
		{
			getblock(ar->mas, dl, n, l, m, k0, q);
			for (int s = 0; s < m; s++)
			{
				b0[s] = ar->b[s+q*m];
			}
			b1 = umnoz(b1, dl, b0, l, m, 1);
			for (int s = 0; s < l; s++)
			{
				ar->b[s+k0*m] = ar->b[s+k0*m]-b1[s];
			}
			for (j = k0; j >= q; j--)
			{
				if (j == k0)
				{
					getblock(ar->mas, dl, n, l, m, k0, q);
					getblock(ar->mas, cl, n, m, l, q, j);
					o = umnoz(o, dl, cl, l, m, l);
					a = 0;
					for ( int s = n-l; s < n; s++)
					{
						for ( int z = n-l; z < n; z++)
						{
							ob[a] = ar->mas[n*s+z];
							a = a+1;
						}
					}
					for (int s=0; s<l; s++)
					{
						for (int z=0; z<l; z++)
						{
							ob[l*s+z]=ob[l*s+z]-o[l*s+z];
						}
					}
					a = 0;
					for ( int s = n-l; s < n; s++)
					{
						for ( int z = n-l; z < n; z++)
						{
							ar->mas[n*s+z] = ob[a];
							a = a+1;
						}
					}
				}
				else
				{
					getblock(ar->mas, dl, n, l, m, k0, q);
					getblock(ar->mas, cm, n, m, m, q, j);
					cl = umnoz(cl, dl, cm, l, m, m);
					getblock(ar->mas, dl, n, l, m, k0, j);
					for (int s=0; s<l; s++)
					{
						for (int z=0; z<m; z++)
						{
							dl[m*s+z]=dl[m*s+z]-cl[m*s+z];
						}
					}
					setblock(ar->mas, dl, n, l, m, k0, j);
				}
			}
		}
		if (((l != 0) || (m == 1)) && (q == k1))
		{
			if (l != 0)
			{
				for (int z = n-l; z < n; z++)
				{
					if (modul(ar->mas[n*(n-1)+z]) >= 5.0e-300)
					{
						t0 = t0+1;
					}
				}
			}
			if (m == 1)
			{
				if (modul(ar->mas[n*n-1]) >= 5.0e-300)
				{
					t0 = t0+1;
				}
			}
			if ((t0 == 0) && (n != 1))
			{
				printf("Бесконечное множество решений\n");
				delete[] omasn;
				delete[] cm;
				delete[] dm;
				delete[] cl;
				delete[] dl;
				delete[] ob;
				delete[] o;
				delete[] b0;
				delete[] b1;
				delete[] omas;
				delete[] c;
				return 0;
			}
		}
		t0 = 0;
	}
	reduce_sum(ar->p);
	if ((q == k0-1) && (k == 0))
	{
		for (int z = n-m; z < n; z++)
		{
			if (modul(ar->mas[n*(n-1)+z]) >= 5.0e-300)
			{
				t0 = t0+1;
			}
		}
		if ((t0 == 0) && (n != 1))
		{
			printf("Бесконечное множество решений\n");
			delete[] omasn;
			delete[] cm;
			delete[] dm;
			delete[] cl;
			delete[] dl;
			delete[] ob;
			delete[] o;
			delete[] b0;
			delete[] b1;
			delete[] omas;
			delete[] c;
			return 0;
		}
		if (l != 0)
		{
			a = 0;
			for ( int i = n-l; i < n; i++)
			{
				for ( int j = n-l; j < n; j++)
				{
					o[a] = ar->mas[n*i+j];
					a = a+1;
				}
			}
			ob = obrat(l, o, ob);
			o = umnoz(o, ob, o, l, l, l);
			a = 0;
			for ( int i = n-l; i < n; i++)
			{
				for ( int j = n-l; j < n; j++)
				{
					ar->mas[n*i+j] = o[a];
					a = a+1;
				}
			}
			for (int s = 0; s < l; s++)
			{
				b1[s] = ar->b[s+k0*m];
			}
			b1 = umnoz(b1, ob, b1, l, l, 1);
			for (int s = 0; s < l; s++)
			{
				ar->b[s+k0*m] = b1[s];
			}
		}
		for (int j = k1; j >= 1; j--)
		{
			for (int i = j-1; i >= 0; i--)
			{
				if (j == k0)
				{
					getblock(ar->mas, dl, n, m, l, i, j);
					a = 0;
					for ( int s = n-l; s < n; s++)
					{
						for ( int z = n-l; z < n; z++)
						{
							o[a] = ar->mas[n*s+z];
							a = a+1;
						}
					}
					for (int s = 0; s < l; s++)
					{
						b1[s] = ar->b[s+j*m];
					}
					b0 = umnoz(b0, dl, b1, m, l, 1);
					for (int s = 0; s < m; s++)
					{
						ar->b[s+i*m] = ar->b[s+i*m]-b0[s];
					}
					cl = umnoz(cl, dl, o, m, l, l);
					for (int s=0; s<m; s++)
					{
						for (int z=0; z<l; z++)
						{
							dl[l*s+z]=dl[l*s+z]-cl[l*s+z];
						}
					}
					setblock(ar->mas, dl, n, m, l, i, j);
				}
				else
				{
					getblock(ar->mas, dm, n, m, m, i, j);
					for (int s = 0; s < m; s++)
					{
						b0[s] = ar->b[s+j*m];
					}
					b0 = umnoz(b0, dm, b0, m, m, 1);
					for (int s = 0; s < m; s++)
					{
						ar->b[s+i*m] = ar->b[s+i*m]-b0[s];
					}
					getblock(ar->mas, cm, n, m, m, j, j);
					cm = umnoz(cm, dm, cm, m, m, m);
					for (int s=0; s<m; s++)
					{
						for (int z=0; z<m; z++)
						{
							dm[m*s+z]=dm[m*s+z]-cm[m*s+z];
						}
					}
					setblock(ar->mas, dm, n, m, m, i, j);
				}
			}
		}
	}
	delete[] omasn;
	delete[] cm;
	delete[] dm;
	delete[] cl;
	delete[] dl;
	delete[] ob;
	delete[] o;
	delete[] b0;
	delete[] b1;
	delete[] omas;
	delete[] c;
	reduce_sum(ar->p);
	return 0;
}

double *gauss(int n, int m, int s1, int p, double *mas, double *b, double *x, char *filename, int r, double *mas5, double *b5)
{
	pthread_t thread;
	Args *a1 = new Args[p+1];
	int k0 = n/m;
	int *nomer = new int[n];
	int t = 0, error0 = 0;
	for (int z=0; z<n; z++)
	{
		nomer[z] = z;
	}
	for (int i=0; i<k0; i++)
	{
		double *stroka = new double[n*m];
		for(int j=0; j<p; j++)
		{
			a1[j].mas = mas;
			a1[j].stroka = stroka;
			a1[j].nomer = nomer;
			a1[j].b = b;
			a1[j].x = x;
			a1[j].n = n;
			a1[j].m = m;
			a1[j].k = j;
			a1[j].p = p;
			a1[j].q = i;
			a1[j].min = 0;
			a1[j].otvet = 0;
			a1[j].s1 = s1;
			a1[j].filename = filename;
			a1[j].r = r;
			a1[j].mas5 = mas5;
			a1[j].b5 = b5;
			a1[j].error = 0;
		}
		for(int j=1; j<p; j++)
		{
			pthread_create(&thread, NULL, solution, a1+j);
		}
		solution(a1);
		delete[] stroka;
	}
	error0 = a1[0].error;
	if (error0 == -1)
	{
		printf("В файле меньше элементов чем заявлено\n");
		delete[] a1;
		delete[] nomer;
		return x;
	}
	if (error0 == -5)
	{
		printf("Бесконечное множество решений\n");
		delete[] a1;
		delete[] nomer;
		return x;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			t = nomer[j];
			if (t == i)
				x[i] = b[j];
		}
	}
	delete[] a1;
	delete[] nomer;
	return x;
}

void reduce_sum(int p)
{
	static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;
	static pthread_cond_t c_out = PTHREAD_COND_INITIALIZER;
	static int t_in = 0;
	static int t_out = 0;
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

void reduce(int p, int *a, double *b)
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
		if (*b > 5.0e-300)
		{
			r = a;
			r1 = b;
		}
	}
	else
	{
		if ((*r1 > *b) && (*b > 5.0e-300))
		{
			*r = *a;
			*r1 = *b;
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

void getblock(double *A, double *C, int n, int r0, int r1, int i, int j)
{
	int k, r;
	if (r0 >= r1)
	{
		for ( k = 0; k < r0; k++ )
		{
			for ( r = 0; r < r1; r++ )
			{
				C[k*r1+r] = A[i*n*r0+j*r0+k*n+r];
			}
		}
	}
	else
	{
		for ( k = 0; k < r0; k++ )
		{
			for ( r = 0; r < r1; r++ )
			{
				C[k*r1+r] = A[i*n*r1+j*r1+k*n+r];
			}
		}
	}
}

void setblock(double *A, double *C, int n, int r0, int r1, int i, int j)
{
	int k, r;
	if (r0 >= r1)
	{
		for ( k = 0; k < r0; k++ )
		{
			for ( r = 0; r < r1; r++ )
			{
				A[i*n*r0+j*r0+k*n+r] = C[k*r1+r];
			}
		}
	}
	else
	{
		for ( k = 0; k < r0; k++ )
		{
			for ( r = 0; r < r1; r++ )
			{
				A[i*n*r1+j*r1+k*n+r] = C[k*r1+r];
			}
		}
	}
}

double *umnoz(double *b, double *c, double *d, int r0, int c0, int c1)
{
	double *a = new double[r0*c1];
	double q = 0;
	for (int i = 0; i < r0; i++)
	{
		for (int j = 0; j < c1; j++)
		{
			a[i*c1+j] = 0;
		}
	}
	for (int i = 0; i < r0; i++)
	{
		for (int k = 0; k < c0; k++) 
		{
			q = c[i*c0+k];
			for (int j = 0; j < c1; j++)
			{
				a[i*c1+j] += q*d[k*c1+j];
			}
		}
	}	
	for (int i = 0; i < r0; i++)
	{
		for (int j = 0; j < c1; j++)
		{
			b[i*c1+j] = a[i*c1+j];
		}
	}
	delete[] a;
	return b;
}

double *obrat(int N, double *matrix, double *matrixinv)
{
	int curr_row = 0, i, j, m = 1, non_zero_found = 1, I, J;
	double sum = 0;
	double *a = new double[N*N];
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			a[N*i+j] = matrix[N*i+j];
			if(i == j)
				matrixinv[i*N+j] = 1;
			else
				matrixinv[i*N+j] = 0;
		}
	}
	while(non_zero_found && curr_row < N)
	{
		non_zero_found = 0;
		for(i = 0; i < N; i++)
		{
			for(j = curr_row; j < N; j++)
			{
				if(!(modul(a[j*N+i]) < 5.0e-300) && !non_zero_found)
				{
					non_zero_found = 1;
					I = i;
					J = j;
				}
			}
		}
		if(non_zero_found)
		{
			if(modul(a[curr_row*N+I]) < 5.0e-300)
			{
				swaprows(a, curr_row, J, N);
				swaprows(matrixinv, curr_row, J, N);
			}
			multrow(matrixinv, N, curr_row, 1/a[curr_row*N+I]);
			multrow(a, N, curr_row, 1/a[curr_row*N+I]);
			for(j = curr_row + 1; j < N; j++)
			{
				if(!(modul(a[j*N+I]) < 5.0e-300))
				{
					plusrows(matrixinv, N, j, curr_row, (-a[j*N+I]) / a[curr_row*N+I]);
					plusrows(a, N, j, curr_row, (-a[j*N+I]) / a[curr_row*N+I]);
				}
			}
			curr_row++;
		}
	}
	if(non_zero_found)
	{
		for(i = N-1; i > 0; i--)
		{
			for(j = 0; j < i; j++)
			{
				plusrows(matrixinv, N, j, i, -a[j*N+i]);
				plusrows(a, N, j, i, -a[j*N+i]);
			}
		}
	}
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			a[N*i+j] = matrix[N*i+j];
		}
	}
	a = umnoz(a, matrixinv, a, N, N, N);
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			sum = sum+modul(a[i*N+j]);
		}
		if (sum < 5.0e-300)
			m = 0;
		sum = 0;
	}
	if (m == 0)
	{
		for(i = 0; i < N; i++)
		{
			for(j = 0; j < N; j++)
			{
				matrixinv[i*N+j] = 0;
			}
		}
	}
	delete[] a;
	return matrixinv;
}

void swaprows(double *matrix, int row1, int row2, int N)
{
	double Z;
	for(int i = 0; i < N; i++)
	{
		Z = matrix[row1*N+i];
		matrix[row1*N+i] = matrix[row2*N+i];
		matrix[row2*N+i] = Z;
	}
}

void plusrows(double *matrix, int N, int row1, int row2, double k)
{
	int i;
	for(i = 0; i < N; i++)
	{
		matrix[row1*N+i] += k * matrix[row2*N+i];
	}
}

void multrow(double *matrix, int N, int row, double k)
{
	int i;
	for(i = 0; i < N; i++)
	{
		matrix[row*N+i] *= k;
	}
}
