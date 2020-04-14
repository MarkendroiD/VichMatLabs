#include "newton.h"

matrix::matrix()
{
	f.open("matrix.txt");
	f >> size;
	a = new double*[size];
	x = new double*[size];
	da = new double*[size];
	dx = new double*[size];

	for (int i = 0; i < size; i++) {
		a[i] = new double[size];
		x[i] = new double[size];
		da[i] = new double[size];
		dx[i] = new double[size];
	}

	x0 = new double[size];
	b = new double[size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			f >> a[i][j];
			f >> x[i][j];
			da[i][j] = a[i][j] * x[i][j];
			dx[i][j] = x[i][j] - 1;
		}
		f >> b[i];
		x0[i] = 0.5; 
	}
	f.close();
}

void matrix::print()
{
	cout << "Исходная матрица\n\n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << " " << a[i][j] << "(x" << j + 1 << ")^" << x[i][j] << " + ";
		}
		cout << b[i] << " = 0" << endl;
	}
}

void matrix::print_fluxion()
{
	cout << "\nНаходим матрицу Якоби\n" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << " " << da[i][j] << "x" << j + 1 << "^" << dx[i][j];
			if (j < size - 1)
				cout << " + ";
		}
		cout << " = 0" << endl;
	}
}

double **matrix::dif()
{
	double **temp;
	temp = new double*[size];

	for (int i = 0; i < size; i++) {
		temp[i] = new double[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp[i][j] = da[i][j] * pow(x0[j], dx[i][j]);
		}
	}
	return temp;
}

double **matrix::inverse()
{
	double **t, **e;
	t = dif();

	e = new double*[size];

	for (int i = 0; i < size; i++)
		e[i] = new double[size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j)
				e[i][j] = 1;
			else
				e[i][j] = 0;
		}
	} 

	double q;
	for (int k = 0; k < size; k++) {
		q = t[k][k];
		for (int g = 0; g < size; g++) {
			e[k][g] /= q;
			t[k][g] /= q;
		}
		for (int i = k + 1; i < size; i++) {
			q = t[i][k];
			for (int j = 0; j < size; j++) {
				e[i][j] -= e[k][j] * q;
				t[i][j] -= t[k][j] * q;
			}
		}
	}
	
	for (int k = size - 1; k >= 0; k--) {
		for (int i = k - 1; i >= 0; i--) {
			q = t[i][k];
			for (int j = 0; j < size; j++) {
				e[i][j] -= e[k][j] * q;
				t[i][j] -= t[k][j] * q;
			}
		}
	}
	return e;
}

double *matrix::func()
{
	double *temp;
	temp = new double[size];

	for (int i = 0; i < size; i++) {
		temp[i] = 0;
		for (int j = 0; j < size; j++) {
			temp[i] += a[i][j] * pow(x0[j], x[i][j]);
		}
		temp[i] += b[i];
	}
	return temp;
}

double matrix::norm(double *arr)
{
	double max = 0;
	for (int i = 0; i < size; i++)
		if (abs(arr[i]) > max)
			max = abs(arr[i]);
	return max;
}

void matrix::iteration()
{
	double **w;
	double *fx;
	double *temp_x;

	w = new double*[size];
	fx = new double[size];
	temp_x = new double[size];

	for (int i = 0; i < size; i++) {
		w[i] = new double[size];
		temp_x[i] = x0[i];
	}

	int k = 1;
	do {
		if (k >= 2) {
			cout << endl << fabs(norm(x0) - norm(temp_x)) << " >= " << E << endl;
		}
		cout << "\nИтерация " << k << endl << endl;
		w = inverse();
		fx = func();
		for (int i = 0; i < size; i++) {
			cout << "x" << i + 1 << " = " << x0[i];
			temp_x[i] = x0[i];
			for (int j = 0; j < size; j++) {
				cout << " - " << w[i][j] << " * " << fx[j];
				x0[i] -= w[i][j] * fx[j];
			}
			cout << " = " << x0[i] << endl;
		}
		cout << "\nПроверка точности: " << norm(x0) << " - " << norm(temp_x) << " = " << fabs(norm(x0) - norm(temp_x)) << endl;
		k++;
	} while (fabs(norm(x0) - norm(temp_x)) >= E);

	cout << fabs(norm(x0) - norm(temp_x)) << " < " << E;
	cout << "\n\nЗаданная точность достигнута\n" << endl;
	cout << "Ответ: \n";
	for (int i = 0; i < size; i++)
		cout << "x" << i + 1 << " = " << x0[i] << endl;
}