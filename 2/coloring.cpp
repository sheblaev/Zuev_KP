#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "func.h"
using namespace std;

vector<vector<int>> read_graph(char *filename, vector<pair<int, int>>& list, vector<int>& edgesc) 
{
	int z = 0, start = 0, end = 0;
	FILE *f;
	f = fopen(filename, "r");
	vector<vector<int>> graph;
	int n, e;
	vector<pair<int, int>> pairs;
	if (fscanf(f, "%d", &z) == 1)
	{
		n = z;
	}
	if (fscanf(f, "%d", &z) == 1)
	{
		e = z;
	}
	vector <int> v(n, 0);
	graph.resize(n, v);
	auto zero = make_pair(0, 0);
	pairs.resize(graph.size(), zero);
	for (int k = 0; k < e; k++) 
	{
		if (fscanf(f, "%d", &z) == 1)
		{
			start = z;
		}
		if (fscanf(f, "%d", &z) == 1)
		{
			end = z;
		}
		auto p1 = make_pair(start, end);
		list.push_back(p1);
		graph[start][end] = 1;
		graph[end][start] = 1;
		pairs[start].first = pairs[start].first+1;
		pairs[end].first = pairs[end].first+1;
		pairs[start].second = start;
		pairs[end].second = end;
	} 
	sort(pairs.begin(), pairs.end());
	for(int i = pairs.size()-1;i >= 0; i--)
	{
		edgesc.push_back(pairs[i].second);
	}
	fclose(f);
	return graph;
}

vector<int> solve(vector<vector<int>>& graph, const vector<int>& edgesc) 
{
	vector<int> vcolors(graph.size(), -1);
	for(auto it : edgesc) 
	{
		int i = it;
		vector<bool> colored(graph.size(), false);
		for (int j = 0; j < graph.size(); j++) 
		{
			if (graph[i][j] == 1) 
			{
				if(vcolors[j] > -1)
				{
					colored[vcolors[j]] = true;
				}
			}
		}
		for (int k = 0; k < graph.size(); k++) 
		{
			if (!colored[k]) 
			{
				vcolors[i] = k;
				break;
			}
		}
	}
	return vcolors;
}
