#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "func.h"
using namespace std;

struct Point 
{
    double x;
    double y;
};

double dist(Point p1, Point p2) 
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

void read(vector<vector<double> >& mas, const int& n, const vector<Point> points) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
	{
            if (i == j) 
	    {
                mas[i][j] = MAXFLOAT;
            } 
	    else 
	    {
                mas[i][j] = dist(points[i], points[j]);
            }
        }
    }
    for (int i = 0; i < n; i++) 
    {
        mas[i][0] = i;
        mas[0][i] = i;
    }
}

int main (int argc, char *argv[]) 
{
	int n = 0, z1 = 0;
	double z = 0;
	char *filename = 0;
	if (argc != 2)
	{
		printf("Usage: %s input\n", argv[0]);
		return 1;
	}
	filename = argv[1];
        FILE *f;
        f = fopen(filename, "r");
        if (fscanf(f, "%d", &z1) == 1)
        {
                n = z1;
        }
	vector<Point> points(n);
	for (int i = 0; i < n; i++)
        {
		Point p;
                if (fscanf(f, "%lf", &z) == 1)
                {
                        p.x = z;
                }
		if (fscanf(f, "%lf", &z) == 1)
                {
                        p.y = z;
                }
		points[i] = p;
	}
	n = n+1;
	vector<vector<double> > mas(n, vector<double>(n));
        read(mas, n, points);
        TSP tsp(mas);
	printf("%lf\n", tsp.get_res());
	fclose(f);
	return 0;
}
