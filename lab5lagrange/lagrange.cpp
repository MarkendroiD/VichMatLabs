#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

class lagrange
{
private:
	double x;
	double *x_values, *y_values;
	int size;
	ifstream f;
public:
	lagrange()
	{
		cout << "Интерполяция полиномом Лагранжа\n";

		f.open("point.txt");
		f >> size;
		x_values = new double[size];
		y_values = new double[size];

		for (int i = 0; i < size; i++)
		{
			f >> x_values[i];
			f >> y_values[i];
		}
		f >> x;
		f.close();
	}
	
	void print() //Вывод на экран
	{
		cout << endl;
		cout << "x";
		cout << "\t\ty" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << x_values[i];
			cout << "\t\t" << y_values[i] << endl;
		}
		cout << endl;
		cout << "x = " << x << endl << endl;
	}

	double interpolate()
	{
		double lagrange_pol = 0;
		double basics_pol;

		for (int i = 0; i < size; i++)
		{
			basics_pol = 1;
			for (int j = 0; j < size; j++)
			{
				if (j == i) continue;
				basics_pol *= (x - x_values[j]) / (x_values[i] - x_values[j]);
				cout << "basics_pol = " << "( " << x << " - " << x_values[j] << " )" << " / " << "( " << x_values[i] << " - " << x_values[j] << " )" << " = " << (x - x_values[j]) / (x_values[i] - x_values[j]) << endl;
			}
			cout << endl;
			lagrange_pol += basics_pol * y_values[i];

			cout << "lagrange_pol = " << basics_pol << " * " << y_values[i]  << " = " << basics_pol * y_values[i] << endl << endl << endl;
		}
		cout << "Answer: " << lagrange_pol << endl;
		return lagrange_pol;
	}
};

int main()
{
	lagrange a;
	a.print();
	a.interpolate();
	return 0;
}