#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cmath>
#include <utility>
using namespace std;

struct SPoint 
{
    pair <int,int> real;
    pair <int,int> absolute;
};

struct v_point 
{
    SPoint s_point;
    double value;
};


class TSP 
{
private:
    vector<v_point> ribes;
    double res;
public:
    TSP (vector<vector<double>>& mas);
    vector<v_point> columns_reduction(vector<vector<double>>& mas);
    vector<v_point> rows_reduction(vector<vector<double>>& mas);
    double sumColummRow(const vector<v_point>& cols, const vector<v_point>& rows);
    double matrix_reduction(vector<vector<double>>& mas);
    vector<SPoint> first_line_S(const vector<vector<double>>& mas);
    vector<double> d_i(const vector<vector<double>>& mas, const vector<SPoint>& s);
    vector<double> d_j(const vector<vector<double>>& mas, const vector<SPoint>& s);
    v_point argmax (const vector<double>& di, const vector<double>& dj, const vector<SPoint>& s);
    vector<vector<double>> matrix_modify(const vector<vector<double>>& mas, SPoint kl);
    pair<bool, double> NGFC (double old_H, int new_H, v_point kl);
    double recursion (vector<vector<double>>& mas, double sum);
    double get_res();
    vector<v_point> get_res_path();
};
