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
	vector<int> edges_counter;
	vector<pair<int, int>> edges;
	vector<vector<int>> graph = read_graph(filename, edges, edges_counter);
	vector<int> colored2 = solve(graph, edges_counter);
	int max = -1;
	for (int i = 0; i < colored2.size(); i++) 
	{
		if (colored2[i] > max) 
		{
			max = colored2[i];
		}
	}
	printf("%d\n", max+1);
	return 0;
}
