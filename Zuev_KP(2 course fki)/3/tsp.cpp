#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "func.h"
using namespace std;

TSP::TSP (vector<vector<double> >& mas) 
{
    double sum = matrix_reduction(mas);
    res = recursion(mas, sum);
}

double TSP::get_res() 
{
    return res;
}

vector<v_point> TSP::get_res_path() 
{
    return ribes;
}

double TSP::recursion (vector<vector<double> >& mas, double sum) 
{
    if (mas.size() > 3) 
    {
        vector<SPoint> s = first_line_S(mas);
        vector<double> di = d_i(mas, s);
        vector<double> dj = d_j(mas, s);
        v_point arg_max = argmax(di, dj, s);
        vector<vector<double>> resize_matrix = matrix_modify(mas, arg_max.s_point);
        double new_sum = matrix_reduction(resize_matrix);
        auto par = NGFC(sum, new_sum, arg_max);
        if (par.first) 
	{
            v_point ribe;
            ribe.value = par.second;
            ribe.s_point = arg_max.s_point;
            ribes.push_back(ribe);
        } 
	else 
	{
            v_point ribe;
            ribe.value = par.second;
            ribe.s_point.absolute.first = arg_max.s_point.absolute.second;
            ribe.s_point.absolute.second = arg_max.s_point.absolute.first;
            ribes.push_back(ribe);
        }
        return recursion(resize_matrix, sum + new_sum);
    } 
    else 
    {
        for(int i = 1; i <= 2; i++)
	{
            for(int j = 1; j <= 2; j++)
	    {
                if(mas[i][j] < MAXFLOAT)
		{
                    v_point ribe;
                    ribe.value = sum;
                    ribe.s_point.absolute.first = mas[i][0];
                    ribe.s_point.absolute.second = mas[0][j];
                    ribes.push_back(ribe);
                }
            }
        }
        mas.clear();
        return ribes.back().value;
    }
}

pair<bool, double> TSP::NGFC (double old_H, int new_H, v_point kl) 
{
    double neg = old_H + kl.value;
    double pos = old_H + new_H;
    if (pos <= neg) 
    {
        auto p = make_pair(true, pos);
        return p;
    } 
    else 
    {
        auto p = make_pair(false, neg);
        return p;
    }
}

double TSP::matrix_reduction(vector<vector<double> >& mas)
{
    vector<v_point> min_cols = columns_reduction(mas);
    vector<v_point> min_rows = rows_reduction(mas);
    return sumColummRow(min_cols,min_rows);
}

double TSP::sumColummRow(const vector<v_point>& cols, const vector<v_point>& rows)
{
    double sum = 0;
    for(auto c : cols)
    {
        sum = sum+c.value;
    }
    for(auto r : rows)
    {
        sum = sum+r.value;
    }
    return sum;
}

vector<v_point> TSP::columns_reduction(vector<vector<double> >& mas) 
{
    int v_size = mas.size();
    vector<v_point> column_value;
    pair <int,int> min_pair;
    for (int i = 1; i < v_size; i++) 
    {
        double min = MAXFLOAT;
        for(int j = 1; j < v_size; j++)
	{
            if(mas[i][j] < min)
	    {
                min = mas[i][j];
                min_pair.first = i;
                min_pair.second = j;
            }
        }
        v_point point;
        point.s_point.real = min_pair;
        point.value = min;
        column_value.push_back(point);
    }
    for(auto k : column_value)
    {
        for(int j = 1; j <= column_value.size(); j++)
	{
            mas[k.s_point.real.first][j] -= k.value;
        }
    }
    return column_value;
}

vector<v_point> TSP::rows_reduction(vector<vector<double> >& mas) 
{
    int v_size = mas.size();
    vector<v_point> row_value;
    pair <int,int> min_pair;
    for (int j = 1; j < v_size; j++) 
    {
        double  min = MAXFLOAT;
        for(int i = 1; i < v_size; i++)
	{
            if(mas[i][j] < min)
	    {
                min = mas[i][j];
                min_pair.first = i;
                min_pair.second = j;
            }
        }
        v_point point;
        point.s_point.real = min_pair;
        point.value = min;
        row_value.push_back(point);
    }
    for(auto k : row_value)
    {
        for(int i = 1; i <= row_value.size(); i++)
	{
            mas[i][k.s_point.real.second] -= k.value;
        }
    }
    return row_value;
}

vector<double> TSP::d_i (const vector<vector<double> >& mas, const vector<SPoint>& s) 
{
    int v_size = mas.size();
    vector<double> result;
    for (auto s_p : s) 
    {
        double min = MAXFLOAT;
        for (int j = 1; j < v_size; j++) 
	{
            if (mas[s_p.real.first][j] < min && j != s_p.real.second) 
	    {
                min = mas[s_p.real.first][j];
            }
        }
        result.push_back(min);
    }
    return result;
}

vector<double> TSP::d_j (const vector<vector<double> >& mas, const vector<SPoint>& s) 
{
    int v_size = mas.size();
    vector<double> result;
    for (auto s_p : s) 
    {
        double min = MAXFLOAT;
        for (int i = 1; i < v_size; i++) 
	{
            if (mas[i][s_p.real.second] < min && i != s_p.real.first) 
	    {
                min = mas[i][s_p.real.second];
            }
        }
        result.push_back(min);
    }
    return result;
}

vector<SPoint> TSP::first_line_S (const vector<vector<double> >& mas) 
{
    int v_size = mas.size();
    vector<SPoint> first_line;
    for (int i = 1; i < v_size; i++) 
    {
        for (int j = 1; j < v_size; j++) 
	{
            if (mas[i][j] == 0) 
	    {
                SPoint s_p;
                s_p.real = make_pair(i, j);
                s_p.absolute = make_pair(mas[i][0], mas[0][j]);
                first_line.push_back(s_p);
            }
        }
    }
    return first_line;
}

v_point TSP::argmax (const vector<double>& di, const vector<double>& dj, const vector<SPoint>& s) 
{
    v_point p;
    double max = -1;
    for (int i = 0; i < di.size(); i++) 
    {
        double temp = di[i] + dj[i];
        if (temp > max) 
	{
            max = temp;
            p.value = max;
            p.s_point.absolute = s[i].absolute;
            p.s_point.real = s[i].real;
        }
    }
    return p;
}

vector<vector<double>> TSP::matrix_modify(const vector<vector<double> >& mas, SPoint kl)
{
    vector<vector<double>> resize_matrix;
    int size = mas.size();
    double a_first;
    double a_second;
    double first;
    double second;
    second = kl.real.second;
    for(int i = 1; i < size; i++)
    {
        if(mas[i][second] == MAXFLOAT)
	{
            a_second = mas[i][0];
            break;
        }
    }
    first = kl.real.first;
    for(int j = 1; j < size; j++)
    {
        if(mas[first][j] == MAXFLOAT)
	{
            a_first = mas[0][j];
            break;
        }
    }
    for(int i = 0; i < size; i++)
    {
        if(mas[i][0] != kl.absolute.first)
	{
            vector<double> resize_row;
            for(int j = 0; j < size; j++)
	    {
                if(mas[0][j] != kl.absolute.second)
		{
                    resize_row.push_back(mas[i][j]);
                }
            }
            resize_matrix.push_back(resize_row);
        }
    }
    size--;
    for(int i = 1; i < size; i++)
    {
        if(resize_matrix[i][0] == a_second)
	{
            first = i;
            break;
        }
    }
    for(int j = 1; j < size; j++)
    {
        if(resize_matrix[0][j] == a_first)
	{
            second = j;
            break;
        }
    }
    resize_matrix[first][second] = MAXFLOAT;
    return resize_matrix;
}
