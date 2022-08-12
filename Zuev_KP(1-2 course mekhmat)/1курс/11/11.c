#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "11.h"
typedef double(*RRFUN)(double t, double x);
typedef enum {SF_OK=0, SF_ERROR} ErrorCode;

static double simp(double a, double b, double ep, RRFUN ffunc);
static double f(double t, double x);
static double func1(double b, double alpha);
double integrate(double a, double b, double n, RRFUN ffunc);
double delenie(double a, double b, double ep, RRFUN func, ErrorCode *error_code, double alpha);

double uravn(double a, double b, double ep, double alpha) //возвращает корень уравнения
{
double r;
ErrorCode ec;
r = delenie(a, b, ep, func1, &ec, alpha);
return r;
}

double delenie(double a, double b, double ep, RRFUN func, ErrorCode *error_code, double alpha) //решает уравнение методом деления пополам
{
	double kon1 = a, ser = 0, kon2 = b, res1 = 0, ser1 = 0, res2 = 0;
	double dlina = b - a;
	ser = (a + b)/2;
	res1 = (*func)(kon1, alpha);
	res2 = (*func)(kon2, alpha);
	*error_code = SF_OK;
	if(res1*res2 >= 0) 
	{
		*error_code = SF_ERROR;
		return 0;
	}
	while(dlina > ep)
	{
		ser = (kon1 + kon2)/2;
		ser1 = (*func)(ser, alpha);
		if(ser1*res1 <= 0)
		{
			kon2 = ser;
			res2 = ser1;
		}
		if (ser1*res1 > 0)
		{
			kon1 = ser;
			res1 = ser1;
		}
		dlina = kon2 - kon1;
	}
	return (kon1 + kon2)/2;
}

double integrate(double a, double b, double ep, RRFUN ffunc) //вычисляет интеграл методом Симпсона 
{
	int n = 2;
	double i1 = simp(a, b, n, ffunc), i2 = simp(a, b, 2*n, ffunc);
	while ((n > 0) && (modul(i2 - i1) > ep) && (n < 67108864))
	{                                              
		i1 = simp(a, b, n, ffunc);
		n = 2*n;
		i2 = simp(a, b, n, ffunc);
	}
	return i2;
}

double modul(double x) //модуль
{
	if (x < 0)
		return -x;
	else 
		return x;
}

static double simp(double a, double b, double n, RRFUN ffunc) //метод Симпсона с N отрезками
{
	int i;
	double h = 0, res1 = 0, res2 = 0, res = 0, x = 0, i1 = 0, i2 = 0, k = 1;
	h = (b-a)/(2*n);
	for(i = 1; i < n-1; i++)
	{
		x = a+2*i*h;
		res1 = res1 + (*ffunc)(x, b);
	}
	for(i = 1; i < n; i++)
	{
		x = a+(2*i-1)*h;
		res2 = res2 + (*ffunc)(x, b);
	}
	res = (h/3)*(2*res1 + 4*res2 + (*ffunc)(a, b) + (*ffunc)(b, b)); 
	return res;
}

static double f(double t, double x) //подынтегральная функция
{
	double k = (x-t)/(sqrt(1+t*t*t*t));
	return k;
}

static double func1(double b, double alpha) //уранвение
{
	double ep = 0.00001, a = 0;
	double k = integrate(a, b, ep, f)-alpha;
	return k;
}
