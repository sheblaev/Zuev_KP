#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <cmath>
#include "func.h"
using namespace std;

vector<point> Steiner::steiner()
{
	vector<point> x;
	point p;
	p.a.first = 10;
	p.a.second = 15;
	append(p);
	return x;
}

