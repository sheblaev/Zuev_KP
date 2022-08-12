#include"iostream"
#include"math.h"
#include"kuslin.h"

using namespace std;

int main()
{
	try
	{	
		int n = 9; 
		double x[] = {1, 1.5, 4.45, 5, 7.8, 9, 11, 14, 15};
		double x0 = 4.589;
		double y0[] = {0, 0};
		double c[] = {-24.49, -0.8174};
		double *y1 = (double*) malloc(n *sizeof(double));
		double *y2 = (double*) malloc(n *sizeof(double));
		if ((y1 == NULL) || (y2 == NULL))
		{
			throw 123;
		}
		for(int i = 0; i < n; i++)
		{
			y1[i] = 0.125*x[i]*x[i]+5-7*x[i];
			y2[i] = 5*sin(x[i]+5);
		}


		klin func1(n, x, y1);
		y0[0] = func1.interpolation(x0);
		klin func2(n, x, y2);
		y0[1] = func2.interpolation(x0);
		for(int i = 0; i < 2; i++)
		{	
			cout<<"Правильный ответ="<< c[i] <<endl;
			cout<<"Мой ответ="<< y0[i] <<endl;
		}
		free(y1);
		free(y2);
	}
	catch(int code)
	{
		cout<<"error "<<endl;
	}
	return 0;
}

