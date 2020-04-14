#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#define E 0.01
using namespace std;

class matrix
{
private:
	ifstream f;
	int size;
	double **a;
	double **x;
	double *b;
	double *x0;
	double **da;
	double **dx;
public:
	matrix();
	void print();
	void print_fluxion();
	double **dif();
	double *func();
	double **inverse();
	void iteration();
	double norm(double *arr);
};
