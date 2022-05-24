#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "func.h"
using namespace std;

int main (int argc, char *argv[]) 
{
	char *filename = 0;
	if (argc != 2)
	{
		printf("Usage: %s input\n", argv[0]);
		return 1;
	}
	filename = argv[1];
	vector<int> edgesc;
	vector<pair<int, int>> edges;
	vector<vector<int>> graph = read_graph(filename, edges, edgesc);
	vector<int> colored = solve(graph, edgesc);
	int max = -1;
	for (int i = 0; i < colored.size(); i++) 
	{
		if (colored[i] > max) 
		{
			max = colored[i];
		}
	}
	printf("%d\n", max+1);
	return 0;
}
