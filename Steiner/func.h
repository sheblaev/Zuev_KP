#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cmath>
#include <utility>
using namespace std;

struct point 
{
	pair<double,double> a;
};

class Steiner
{
	private:
		int nv;
		int ns;
		vector<point> v;
		vector<point> s;

	public:
		vector<point> steiner();

		Steiner(vector<point> v_point, int n)
		{
			ns = 0;
			nv = n;
			set(v_point, nv);
		}

		void set(vector<point> v_point, int n)
		{
			int i;
			for (i = 0; i < n; i++)
			{
				v.push_back(v_point[i]);
			}
		}

		void get()
		{
			int i;
			printf("v_point\n");
			for (i = 0; i < nv; i++)
			{
				printf("%f %f\n", v[i].a.first, v[i].a.second);
			}
			printf("s_point\n");
			for (i = 0; i < ns; i++)
			{
				printf("%f %f\n", s[i].a.first, s[i].a.second);
			}
		}
		
		void append(point s_point)
		{
			ns = ns+1;
			s.push_back(s_point);	
		}
};
