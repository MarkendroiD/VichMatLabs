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

double mOfChords(double *l, double *AB, int n)
{
	double x;
	int s = 0; 

	while(abs(AB[0] - AB[1]) >= eps && s < 100)
	{
		x = AB[0] - ((f(l, AB[0], n))/(f(l, AB[1], n) - f(l, AB[0], n))) * (AB[1] - AB[0]);
		if (abs(x) < eps)
			x = 0;
		double F1 = 0, F2 = 0, FX = 0;
		FX = f(l, x, n);
		F1 = f(l, AB[0], n);
		F2 = f(l, AB[1], n);
		
		if (abs(FX) < eps)
		{
			FX = 0;
			cout << "Количество итераций: " << s << endl; 
			return x;
		}
		if (F1*FX < 0)
			AB[1] = x;
		else
			AB[0] = x;

		//cout << "\t" << s << "\t" << AB[0] << "\t" << AB[1]<< endl;

		s++;
	}
	cout << "Количество итераций: " << s << endl;
	return x;
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
				double x = mOfChords(l, AB, n);
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