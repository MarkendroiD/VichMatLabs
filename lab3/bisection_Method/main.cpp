#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

const double eps = 0.01;

// Вывод в терминал уравнения
void printUrav(double *l, double *AB, int n)
{
	int k = n;
	cout << "\nДанная функция:\nF(x) = ";
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

//Проверка границ на противоположные знаки
double check(double *l, double *AB, int n)
{
	double F1 = 0, F2 = 0;
	int k = n;
	for (int i = 0; i < n; i++)
	{
		k--;
		if (k != 0){
			F1 = F1 + l[i] * pow(AB[0], k);
			F2 = F2 + l[i] * pow(AB[1], k);
		}
		else 
		{
			F1 = F1 + l[i];
			F2 = F2 + l[i];
		}
		
	}
	if (abs(F1) < eps)
		F1 = 0;
	if (abs(F2) < eps)
		F2 = 0;
	cout << "F(" << AB[0] << ") = " << F1 << endl;
	cout << "F(" << AB[1] << ") = " << F2 << endl;
	if (F1*F2 >= 0)
	{
		if (abs(F1) < eps)
		{
			cout << "Т.к. F("<< AB[0] << ") = "<< F1 << ", то искомый x = " << AB[0] << endl;
			return n;
		}
		if (abs(F2) < eps)
		{
			cout << "Т.к. F("<< AB[1] << ") = "<< F2 << ", то искомый x = " << AB[1] << endl;
			return n;
		}
		cout << "Решений либо нет, либо больше 1, т.к. функция на заданных границах одного знака" << endl;
		return NULL;
	}
	return n;
}

double *bisection()
{

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
		}
	}

}