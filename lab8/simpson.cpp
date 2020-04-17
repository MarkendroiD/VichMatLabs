#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

double function(double function)
{
	return pow(function, 2);
}

double Point(int i, double size)
{
	if (i == size - 1 || i == 0)
		return 1;
	if (i % 2 != 0 || i == 1)
		return 4;
	else
		return 2;
}

int main()
{
	double a, b;
	double answer = 0;
	int size;
	cout << "Enter the number of points: ";
	cin >> size;
	cout << endl << "Enter the left boundary of the integration a = ";
	cin >> a;
	cout << endl << "Enter the right boundary of the integration b = ";
	cin >> b;
	
	if (b > a && size % 2 != 0 && size >= 3)
		for (int i = 0; i < size; i++)
		{
			answer += ((b - a) / ((size - 1) * 3)) * (Point(i, size) * function(i * ((b - a) / (size - 1))));
		}
	else cout << "Error" << endl;
	
	cout << endl << answer << endl;
	system("pause");
}