#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

const double eps = 0.0001;

// Вывод в терминал уравнения
void printUrav(double *l, double *AB, int n)
{
	int k = n;
	cout << "\nДана функция:\nF(x) = ";
	for (int i = 0; i < n; i++)
	{
		k -= 1;
		cout << l[i];
		if (k != 0)
			cout << "*x^" << k;
		if (i < n - 1)
			cout << " + ";
	}
	cout << "\nНа отрезке:\n";
	cout << "[" << AB[0] << " ; " << AB [1] << "]\n"<< endl;
}

//Возврат значения функции
double f (double *l, double x, int n) 
{
	double F = 0;
	int k = n;
	for (int i = 0; i < n; i++)
	{
		k--;
		if (k != 0){
			F = F + l[i] * pow(x, k);
		}
		else 
		{
			F = F + l[i];
		}
		
	}
	if (abs(F) < eps)
		F = 0;
	return F;
}

//Возврат значения производной
double df (double *l, double x, int n)
{
	double F = 0;
	int k = n - 1;
	for (int i = 0; i < n - 1; i++)
	{
		k--;
		if (k != 0){
			F = F + l[i] * pow(x, k) * (k + 1);
		}
		else 
		{
			F = F + l[i];
		}
		
	}
	if (abs(F) < eps)
		F = 0;
	return F;
}

//Возврат значения второй производной
double d2f (double *l, double x, int n)
{
	double F = 0;
	int k = n - 2;
	for (int i = 0; i < n - 2; i++)
	{
		k--;
		if (k != 0){
			F = F + l[i] * pow(x, k) * (k + 2) * (k + 1);
		}
		else 
		{
			F = F + l[i] * (k + 2) * (k + 1);
		}
		
	}
	if (abs(F) < eps)
		F = 0;
	return F;
}

//Проверка границ на противоположные знаки
double check(double *l, double *AB, int n)
{
	double F1 = 0, F2 = 0;
	F1 = f(l, AB[0], n);
	F2 = f(l, AB[1], n);
	
	cout << "F(" << AB[0] << ") = " << F1 << endl;
	cout << "F(" << AB[1] << ") = " << F2 << endl;
	if (F1*F2 >= 0)
	{
		if (abs(F1) < eps)
		{
			cout << "Т.к. F("<< AB[0] << ") = "<< F1 << ", то искомый x = " << AB[0] << endl;
			return 228;
		}
		if (abs(F2) < eps)
		{
			cout << "Т.к. F("<< AB[1] << ") = "<< F2 << ", то искомый x = " << AB[1] << endl;
			return 228;
		}
		cout << "Решений либо нет, либо больше 1, т.к. функция на заданных границах одного знака" << endl;
		return NULL;
	}
	cout << "Функции на границах имеют разные знаки, значит 1 решение" << endl;
	return n;
}

double newton(double *l, double *AB, int n)
{
	double x, xn;
	int s = 0; 
	if (f(l, AB[0], n) * d2f(l, AB[0], n) > 0)
			x = AB[0];
	else
		x = AB[1];
	if (abs(x) < eps)
		x = 0;

	while(abs(x - xn) > eps && s < 100)
	{
		x = xn;
		//cout << f (l, x, n) << endl;
		//cout << df (l, x, n) << endl;
		xn = x - f (l, x, n) / df(l, x, n);

		
		if (abs(xn) < eps)
		{
			xn = 0;
			cout << "Количество итераций: " << s << endl; 
			return xn;
		}

		//cout << "\t" << s << "\t" << AB[0] << "\t" << AB[1]<< endl;

		s++;
	}
	cout << "Количество итераций: " << s << endl;
	return xn;
}

int main()
{
	double *l, *AB; //l - Дин. массив коэф. и своб член
									//AB - дин. массив отрезка
	int n;					//Кол-во l + AB

	for (int k = 1; k < 5; k++)
	{
		string path = to_string(k) + ".txt";
		ifstream in(path);
		if (in.is_open())
		{
			in >> n;
			l = new double[n];
			for (int i = 0; i < n; i++)
			{
				in >> l[i];
			}
			AB = new double[2];
			for (int i = 0; i < 2; i++)
			{
				in >> AB[i];
			}
			printUrav(l, AB, n);
			int CH = check(l, AB, n);
			if (CH == NULL)
				continue;
			if (CH != 228) 
			{
				double x = newton(l, AB, n);
				int alO = x * (10.0/eps);
				if (alO % 10 >= 5) 
					alO +=10;
				alO = alO/10;
				x = (double)alO * eps; 
				cout << "Ответ с точностью eps = "<< eps << ":\t" << x << endl;
			}
		}
	}
	return 0;
}