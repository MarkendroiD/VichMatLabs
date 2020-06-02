#include <iostream>
#include <cmath>

using namespace std;

double f(double x, double y)
{
	return 3 * powl(x, 2) + sqrt(y);
}

int main()
{
	cout << "Уравнение: y' = 3x^2 + sqrt(y)" << endl;

	double x = 0, y = 1, h = 0.4;
	int iterS = 2 / h;
	
	cout << "Шаг: h = " << h << endl;
	cout << "Количество итераций = " << iterS << endl;
	cout << "Начальные точки:" << endl;
	cout << "x0 = " << x << endl;
	cout << "y0 = " << y << endl;
	cout << "Промежуток [" << x << "; " << iterS * h << "]" << endl;

	for (int i = 0; i < iterS; i++) 
	{
		double q = x + h / 2;
		double r = y + (h / 2) * f(x, y);
		double dy = h * f(q, r);
		y += dy;
		x += h;
		cout << "x = " << x << "\t y = " << y << endl;
	}
	cout << "\n" << "Ответ: " << "x = " << x << "; y = " << y << endl;
	return 0;
}