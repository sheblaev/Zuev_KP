#include"iostream"
#include"math.h"

using namespace std;



class klin
{
	private:
		int n;
		double *x;
		double *y;	
	public:


		klin(int dlina, double *a, double *b)
		{	
			n = dlina;
			x = (double*) malloc(n *sizeof(double));
			y = (double*) malloc(n *sizeof(double));


			for(int i = 0; i < n; i++)
			{
				x[i] = a[i];
				y[i] = b[i];
			}

		}

		double interpolation(double x0)
		{
			double y0 = 0;
			double h = 0, k = 0;
			if ((y == NULL) || (x == NULL))
			{
				throw 0;
			}
			for(int i = 1; i < n; i ++)
			{
				if ((x[i-1]<=x0) && (x0<=x[i]))
				{
					h = (y[i]-y[i-1])/(x[i]-x[i-1]);
					k = y[i-1]-h*x[i-1];
					y0 = h*x0+k;
				}
			}
			return y0;
		}
		~klin()
		{

			free(x);
			free(y);
		}
};























