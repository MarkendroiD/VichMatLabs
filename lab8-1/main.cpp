#include <iostream>
#include <math.h>

using namespace std;

double EPS = 0.01;		// точность
int N = 50;			// кол-во разбиений
double A = 0, B = 6;	// интервал

double f(double x)
{
	double F = cos(x)*2*x + 10;

	int E = F * (10.0/EPS);
	if (E % 10 >= 5) 
		E +=10;
	E = E/10;
	F = (double)E * EPS;

	return F;
}

int main()
{
	double res[4]; 

	cout << "\nНайти интеграл от функции: " << endl;
	cout << "\tcos(x)*2x + 10 при eps = "<< EPS << " и количеством разбиений n = "<< N << " на интервале от "<< A << " до " << B << endl;
	cout << "Методами трапеций и Симпсона с двойным пересчетом" << endl;
	
	for (int k = 1; k < 3; k++)
	{
		double summT = (f(A) + f(B)) / 2;
		double h = (B - A) / (N * k);

		for (double i = 1; i <= (N * k) - 1; i ++)
		{
			summT += f(A + h * i);
		}

		double answerT = summT * h;

		int Et = answerT * (10.0/EPS);
		if (Et % 10 >= 5) 
			Et +=10;
		Et = Et/10;
		answerT = (double)Et * EPS;
		res[k] = answerT;
		cout << "\nМетод трапеций при n = " << N * k << ": " << answerT << endl;

		double summS = f(A) + f(B);

		for (int i = 1; i <= (N * k) - 1; i+=2)
		{
			summS += 2*f(A + h * (i+1));
			summS += 4*f(A + h * i);
		}
		summS -= 2*f(B);

		double answerS = (summS* h) / 3;
		
		int Es = answerS * (10.0/EPS);
		if (Es % 10 >= 5) 
			Es +=10;
		Es = Es/10;
		answerS = (double)Es * EPS;
		res[k+2] = answerS;
		cout << "\nМетод Симпсона при n = " << N * k<< ": " << answerS << endl << endl;
		if (k == 1) cout << "ДВОЙНОЙ ПЕРЕСЧЕТ:" << endl;
	}
	cout << "Проверка погрешности при n и 2n:" << endl;
	cout << "Метод трапеций:\t|" << res[1] << " - " << res[2] << "| = " << res[1] - res [2] << " <= eps" << endl;
	cout << "Метод Симпсона:\t|" << res[3] << " - " << res[4] << "| = " << res[3] - res [4] << " <= eps" << endl;
	return 0;
}