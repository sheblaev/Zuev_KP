#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
using namespace std;

vector<vector<int>> read_graph(char *filename, vector<pair<int, int>>& list, vector<int>& edgesc);
vector<int> solve(vector<vector<int>>& graph, const vector<int>& edgesc);
