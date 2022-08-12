#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "func.h"
using namespace std;
void getblock(double *A, double *C, int n, int r0, int r1, int i, int j);
void setblock(double *A, double *C, int n, int r0, int r1, int i, int j);
int glavelem(int n, int s, double *mas, int m);
double *umnoz(double *b, double *c, double *d, int r0, int c0, int c1);
double *obrat(int N, double *matrix, double *matrixinv);
void swaprows(double *matrix, int row1, int row2, int N);
void plusrows(double *matrix, int N, int row1, int row2, double k);
void multrow(double *matrix, int N, int row, double k);

double *gauss(int n, int m, double *mas, double *b, double *x)
{
	int a, k, j, i, l, p, k1, t, t0;
	int max = 0;
	k = n/m;
	k1 = k;
	l = n-m*k;
	if (l == 0)
	{
		k1 = k-1;
	}
	double *omasn = new double[n*n];
	double *omas = new double[m*m];
	double *cm = new double[m*m];
	double *dm = new double[m*m];
	double *cl = new double[m*l];
	double *dl = new double[m*l];
	double *ob = new double[l*l];
	double *o = new double[l*l];
	double *b0 = new double[m];
	double *b1 = new double[l];
	int *nomer = new int[n];
	t = 0;
	t0 = 0;
	if (n <= 14)
	{
		omasn = obrat(n, mas, omasn);
		for (int z = 0; z < n; z++)
		{
			for (int q = 0; q < n; q++)
			{
				if (modul(omasn[n*z+q]) >= 5.0e-300)
				{
					t0 = t0+1;
				}
			}
		}
		if ((t0 == 0) && (n != 1))
		{
			printf("Бесконечное множество решений\n");
			delete[] omasn;
			delete[] omas;
			delete[] cm;
			delete[] dm;
			delete[] cl;
			delete[] dl;
			delete[] ob;
			delete[] o;
			delete[] b0;
			delete[] b1;
			delete[] nomer;
			return x;
		}
	}
	t0 = 0;
	for (int z = 0; z < n; z++)
	{
		nomer[z] = z;
	}
	for (p = 0; p < k; p++)
	{
		if (m == 1)
		{
			max = p;
			if (modul(mas[n*p+p]) <= 5.0e-300)
				max = glavelem(n, p, mas, m);
			for (j = p; j < k; j++)
			{
				getblock(mas, cm, n, m, m, j, max);
				getblock(mas, dm, n, m, m, j, p);
				setblock(mas, cm, n, m, m, j, p);
				setblock(mas, dm, n, m, m, j, max);
			}
			for (int z = p*m; z < p*m+m; z++)
			{
				t = nomer[z];
				nomer[z] = nomer[z+max*m-p*m];
				nomer[z+max*m-p*m] = t;
			}
		}
		else
		{
			max = glavelem(n, p, mas, m);
			for (j = p; j < k; j++)
			{
				getblock(mas, cm, n, m, m, j, max);
				getblock(mas, dm, n, m, m, j, p);
				setblock(mas, cm, n, m, m, j, p);
				setblock(mas, dm, n, m, m, j, max);
			}
			if (l != 0)
			{
				getblock(mas, cl, n, l, m, k, max);
				getblock(mas, dl, n, l, m, k, p);
				setblock(mas, cl, n, l, m, k, p);
				setblock(mas, dl, n, l, m, k, max);
			}
			for (int z = p*m; z < p*m+m; z++)
			{
				t = nomer[z];
				nomer[z] = nomer[z+max*m-p*m];
				nomer[z+max*m-p*m] = t;
			}
		}
		getblock(mas, cm, n, m, m, p, p);
		omas = obrat(m, cm, omas);
		for (j = 0; j < k; j++)
		{
			getblock(mas, cm, n, m, m, p, j);
			cm = umnoz(cm, omas, cm, m, m, m);
			setblock(mas, cm, n, m, m, p, j);
		}
		if (l != 0)
		{
			getblock(mas, cl, n, m, l, p, k);
			cl = umnoz(cl, omas, cl, m, m, l);
			setblock(mas, cl, n, m, l, p, k);
		}
		for (i = 0; i < m; i++)
		{
			b0[i] = b[i+p*m];
		}
		b0 = umnoz(b0, omas, b0, m, m, 1);
		for (i = 0; i < m; i++)
		{
			b[i+p*m] = b0[i];
		}
		for (i = p+1; i < k; i++)
		{
			getblock(mas, dm, n, m, m, i, p);
			for (int q = 0; q < m; q++)
			{
				b0[q] = b[q+p*m];
			}
			b0 = umnoz(b0, dm, b0, m, m, 1);
			for (int q = 0; q < m; q++)
			{
				b[q+i*m] = b[q+i*m]-b0[q];
			}
			for (j = k1; j >= p; j--)
			{
				if (j == k)
				{
					getblock(mas, dm, n, m, m, i, p);
					getblock(mas, cl, n, m, l, p, j);
					cl = umnoz(cl, dm, cl, m, m, l);
					getblock(mas, dl, n, m, l, i, j);
					for (int q=0; q<m; q++)
					{
						for (int z=0; z<l; z++)
						{
							dl[l*q+z]=dl[l*q+z]-cl[l*q+z];
						}
					}
					setblock(mas, dl, n, m, l, i, j);
				}
				else
				{
					getblock(mas, dm, n, m, m, i, p);
					getblock(mas, cm, n, m, m, p, j);
					cm = umnoz(cm, dm, cm, m, m, m);
					getblock(mas, dm, n, m, m, i, j);
					for (int q=0; q<m; q++)
					{
						for (int z=0; z<m; z++)
						{
							dm[m*q+z]=dm[m*q+z]-cm[m*q+z];
						}
					}
					setblock(mas, dm, n, m, m, i, j);
				}
			}
		}
		if (l != 0)
		{
			getblock(mas, dl, n, l, m, k, p);
			for (int q = 0; q < m; q++)
			{
				b0[q] = b[q+p*m];
			}
			b1 = umnoz(b1, dl, b0, l, m, 1);
			for (int q = 0; q < l; q++)
			{
				b[q+k*m] = b[q+k*m]-b1[q];
			}
			for (j = k; j >= p; j--)
			{
				if (j == k)
				{
					getblock(mas, dl, n, l, m, k, p);
					getblock(mas, cl, n, m, l, p, j);
					o = umnoz(o, dl, cl, l, m, l);
					a = 0;
					for ( int q = n-l; q < n; q++)
					{
						for ( int z = n-l; z < n; z++)
						{
							ob[a] = mas[n*q+z];
							a = a+1;
						}
					}
					for (int q=0; q<l; q++)
					{
						for (int z=0; z<l; z++)
						{
							ob[l*q+z]=ob[l*q+z]-o[l*q+z];
						}
					}
					a = 0;
					for ( int q = n-l; q < n; q++)
					{
						for ( int z = n-l; z < n; z++)
						{
							mas[n*q+z] = ob[a];
							a = a+1;
						}
					}
				}
				else
				{
					getblock(mas, dl, n, l, m, k, p);
					getblock(mas, cm, n, m, m, p, j);
					cl = umnoz(cl, dl, cm, l, m, m);
					getblock(mas, dl, n, l, m, k, j);
					for (int q=0; q<l; q++)
					{
						for (int z=0; z<m; z++)
						{
							dl[m*q+z]=dl[m*q+z]-cl[m*q+z];
						}
					}
					setblock(mas, dl, n, l, m, k, j);
				}
			}
		}
		if (((l != 0) || (m == 1)) && (p == k1-1))
		{
			if (l != 0)
			{
			for (int z = n-l; z < n; z++)
			{
				if (modul(mas[n*(n-1)+z]) >= 5.0e-300)
				{
					t0 = t0+1;
				}
			}
			}
			if (m == 1)
                        {
                                if (modul(mas[n*n-1]) >= 5.0e-300)
                                {
                                        t0 = t0+1;
                                }
			}
			if ((t0 == 0) && (n != 1))
			{
				printf("Бесконечное множество решений\n");
				delete[] omasn;
				delete[] omas;
				delete[] cm;
				delete[] dm;
				delete[] cl;
				delete[] dl;
				delete[] ob;
				delete[] o;
				delete[] b0;
				delete[] b1;
				delete[] nomer;
				return x;
			}
		}
		t0 = 0;
	}
	for (int z = n-m; z < n; z++)
	{
		if (modul(mas[n*(n-1)+z]) >= 5.0e-300)
		{
			t0 = t0+1;
		}
	}
	if ((t0 == 0) && (n != 1))
	{
		printf("Бесконечное множество решений\n");
		delete[] omasn;
		delete[] omas;
		delete[] cm;
		delete[] dm;
		delete[] cl;
		delete[] dl;
		delete[] ob;
		delete[] o;
		delete[] b0;
		delete[] b1;
		delete[] nomer;
		return x;
	}
	t0 = 0;
	if (l != 0)
	{
		a = 0;
		for ( i = n-l; i < n; i++)
		{
			for ( j = n-l; j < n; j++)
			{
				o[a] = mas[n*i+j];
				a = a+1;
			}
		}
		ob = obrat(l, o, ob);
		o = umnoz(o, ob, o, l, l, l);
		a = 0;
		for ( i = n-l; i < n; i++)
		{
			for ( j = n-l; j < n; j++)
			{
				mas[n*i+j] = o[a];
				a = a+1;
			}
		}
		for (int q = 0; q < l; q++)
		{
			b1[q] = b[q+k*m];
		}
		b1 = umnoz(b1, ob, b1, l, l, 1);
		for (int q = 0; q < l; q++)
		{
			b[q+k*m] = b1[q];
		}
	}
	for (j = k1; j >= 1; j--)
	{
		for (i = j-1; i >= 0; i--)
		{
			if (j == k)
			{
				getblock(mas, dl, n, m, l, i, j);
				a = 0;
				for ( int q = n-l; q < n; q++)
				{
					for ( int z = n-l; z < n; z++)
					{
						o[a] = mas[n*q+z];
						a = a+1;
					}
				}
				for (int q = 0; q < l; q++)
				{
					b1[q] = b[q+j*m];
				}
				b0 = umnoz(b0, dl, b1, m, l, 1);
				for (int q = 0; q < m; q++)
				{
					b[q+i*m] = b[q+i*m]-b0[q];
				}
				cl = umnoz(cl, dl, o, m, l, l);
				for (int q=0; q<m; q++)
				{
					for (int z=0; z<l; z++)
					{
						dl[l*q+z]=dl[l*q+z]-cl[l*q+z];
					}
				}
				setblock(mas, dl, n, m, l, i, j);
			}
			else
			{
				getblock(mas, dm, n, m, m, i, j);
				for (int q = 0; q < m; q++)
				{
					b0[q] = b[q+j*m];
				}
				b0 = umnoz(b0, dm, b0, m, m, 1);
				for (int q = 0; q < m; q++)
				{
					b[q+i*m] = b[q+i*m]-b0[q];
				}
				getblock(mas, cm, n, m, m, j, j);
				cm = umnoz(cm, dm, cm, m, m, m);
				for (int q=0; q<m; q++)
				{
					for (int z=0; z<m; z++)
					{
						dm[m*q+z]=dm[m*q+z]-cm[m*q+z];
					}
				}
				setblock(mas, dm, n, m, m, i, j);
			}
		}
	}
	t = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			t = nomer[j];
			if (t == i)
				x[i] = b[j];
		}
	}
	delete[] omasn;
	delete[] omas;
	delete[] cm;
	delete[] dm;
	delete[] cl;
	delete[] dl;
	delete[] ob;
	delete[] o;
	delete[] b0;
	delete[] b1;
	delete[] nomer;
	return x;
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

int glavelem(int n, int s, double *mas, int m)
{
	double sum = 0, min = 0;
	int i = s, j, k, z, q = 0;
	double *omas = new double[m*m];
	double *c = new double[m*m];
	if (m != 1)
	{
		for (j = i; j < n/m; j++)
		{
			getblock(mas, c, n, m, m, i, j);
			obrat(m, c, omas);
			for (k = 0; k < m; k++)
			{
				for (z = 0; z < m; z++)
				{
					sum = sum+modul(omas[k*m+z]);
				}
			}
			if (((min >= sum) || (min <= 5.0e-300)) && (sum >= 5.0e-300))
			{
				min = sum;
				q = j;
			}
			sum = 0;
		}
	}
	else
	{
		for (k = 0; k < n; k++)
		{
			sum = modul(mas[i*n+k]);
			if (((min >= sum) || (min <= 5.0e-300)) && (sum >= 5.0e-300))
			{
				min = sum;
				q = k;
			}
			sum = 0;
		}
	}
	delete[] omas;
	delete[] c;
	return q;
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
