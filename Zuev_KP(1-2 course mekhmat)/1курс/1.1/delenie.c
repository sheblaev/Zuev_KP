#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"delenie.h"

double delenie(double a, double b, double ep, RRFUN func, ErrorCode *error_code)
{
	double kon1 = a, ser = 0, kon2 = b, res1 = 0, ser1 = 0, res2 = 0;
	double dlina = b - a;
	ser = (a + b)/2;
	res1 = (*func)(kon1);
	res2 = (*func)(kon2);
	*error_code = SF_OK;
	if(res1*res2 >= 0) 
	{
		*error_code = SF_ERROR;
		return 0;
	}
	while(dlina > ep)
	{
		ser = (kon1 + kon2)/2;
		ser1 = (*func)(ser);
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


