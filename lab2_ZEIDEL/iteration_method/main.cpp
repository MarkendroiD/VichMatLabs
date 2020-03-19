#include <iostream>
#include <fstream>
#include <string>

using namespace std;



void matrixPrint(double **a, double *y, int n)
{
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			cout << a[i][j] << "*x" << j;
			if (j < n - 1)
			cout << " + ";
		}
		cout << " = " << y[i] << endl;
	}
	return;
}

double *check(double **a, double *y, int n)
{

	// Копирование матрицы для проверки
	double **A, *Y, *lol;
	A = new double *[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
	}
	
	Y = new double [n];
	copy(y, y + n, Y);

	for (int i = 0; i < n; i++)
	{
		copy(a[i], a[i] + n, A[i]);
	}

	//Проверка матрицы на совместность по
	//теореме Кронекера-Капелли

	int rang = 0;	//Ранг матрицы системы
	int rangExt = 0;//Ранг расширенной матрицы

	//Если rang != rangExt, то СЛАУ несовместна
	//Если rang == rangExt < n, то СЛАУ является 
	//неопределенной (бесконечное кол-во решений)
	//Если rang == rangExt == n, то СЛАУ является 
	//определенной (1 решение)

	double max;
	int k, index;
	const double eps = 0.0001;
	k = 0;
	if (n == 1){
		if(A[0][0] == 0 && Y[0] == 0)
		{
			cout << "Бесконечное кол-во решений" << endl;
			return NULL;
		}
	}
	while (k < n)
	{
		max = abs(A[0][0]);
		index = k;
		for (int i = k; i < n; i++) 
		{
			if (abs(A[i][k]) > max)
			{
				max = abs(A[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max != abs(A[k][k]))
		{
			for (int j = k; j < n; j++) 
			{
				double temp = A[k][j];
				A[k][j] = A[index][j];
				A[index][j] = temp;

			}
			double temp = Y[k];
			Y[k] = Y[index];
			Y[index] = temp;
		}
		//matrixPrint(A, Y, n);
		for (int i = k; i < n; i++) 
		{
			//matrixPrint(a, y, n);
			//cout << endl;
			double temp = A[i][k];
			if (abs(temp) < eps) continue;
			for (int j = 0; j < n; j++) 
				A[i][j] = A[i][j] / temp;
			Y[i] = Y[i] / temp;
			//matrixPrint(A, Y, n);

			if (i == k)  continue;
			for (int j = 0; j < n; j++)
				A[i][j] = A[i][j] - A[k][j];
			Y[i] = Y[i] - Y[k];
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int h = A[i][j] * (10.0/eps);
				if (h % 10 >= 5) 
				{
					h+=10;
				}
				h = h/10;
				A[i][j] = (double)h  * eps;
				int l = Y[i] * (10.0/eps);
				if (l % 10 >= 5) 
				{
					l+=10;
				}
				l = l/10;
				Y[i]= (double)l  * eps;
			}
		}
		//matrixPrint(A, Y, n);
		k++;
	}
	int flag = 0; //Кол-во нулей в строке
	int flag1 = 0;//Кол-во нулевых строк матрицы
	int flag2 = 0;//Кол-во нулевых строк расш. матрицы
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A[i][j] == 0)
			{
				flag++;
				if (flag == n)
					flag1++;
			}
		}
		if (Y[i] == 0 && flag == n)
		{	
			flag2++;
			
		}
		flag = 0;

	}
	cout << "Преобразованная матрица:\n" << endl;
	matrixPrint(A, Y, n);
	rang = n - flag1;
	cout << endl <<"Ранг матрицы коэф-ов: " << rang << endl;
	rangExt = n - flag2;
	cout << "Ранг расш. матрицы: " << rangExt << endl;
	if (rang != rangExt)
	{
		cout << "Ранги не равны -> Система не совместна -> Решений нет" << endl;
		return NULL;
	}
	else
	{
		cout << "Ранги равны -> Система совместна" << endl;
		if (rang < n)
		{
			cout << "Ранги меньше кол-ва неизвестных -> Бесконечное кол-во решений" << endl;
			return 0;
		}
		if (rang == n)
		{
			cout << "Ранги равны кол-ву неизвестных -> СЛАУ имеет 1 решение\n" << endl;
		}
	}

	lol = new double[n];
	
	delete[] Y;
	return lol;
}

double * zeidel(double **a, double *y, int n) 
{

	double *x, max;
	int k, index;
	const double eps = 0.01;
	x = new double[n];
	k = 0;
	if (n == 1){
	if(a[0][0] == 0 && y[0] == 0)
		cout << "Бесконечное кол-во решений" << endl;
	delete[] a;
	delete[] y;
	return NULL;
	}
	//Цикл перестановки строк, чтобы по 
	//диагонали были максимальные значения
	while (k < n)
	{
		max = abs(a[k][k]);
		index = k;
		for (int i = k; i < n; i++) 
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		if (max != abs(a[k][k]))
		{
			for (int j = 0; j < n; j++) 
			{
				double temp = a[k][j];
				a[k][j] = a[index][j];
				a[index][j] = temp;
				double temp1 = y[k];
				y[k] = y[index];
				y[index] = temp1;
			}
		}
		k++;
	}


	//matrixPrint(a, y, n);
	//cout << endl;


	// Деление строк на диагональные значения
	for (int i = 0; i < n; i++)
	{
		double delitel = a[i][i];
		y[i] /= delitel;
		for (int l = 0; l < n; l++)
		{
			a[i][l] /= delitel;
		}
	}
	//matrixPrint(a, y, n);
	cout << endl;
/*
	for (int i = 0; i < n; i++)
	{
		cout << x[i] << endl;
	}
*/
	double *prevX;
	prevX = new double[n];



	int s = 0;
	while (s < 100)
	{
		double tempX[n];
		for(int i = 0; i < n; i++)
		{	
			double tempY[n];
			tempY[i] = y[i];
			
			tempX[i] = x[i];
			for (int j = 0; j < n; j++)
			{
				if (i != j)
				{
					tempX[i] = tempY[i] - a[i][j] * x[j];
					tempY[i] = tempX[i];
					//cout << tempY[i] << "\t";
				}
				
			}
			//cout << endl;
		}
		//cout << endl;



		for (int i = 0; i < n; i++)
		{
			int h = tempX[i] * (10.0/eps);
			if (h % 10 >= 5) 
				h+=10;
			h = h/10;
			tempX[i] = (double)h  * eps;
			int l = prevX[i] * (10.0/eps);
			if (l % 10 >= 5) 
				l+=10;
			l = l/10;
			prevX[i] = (double)l  * eps;
			x[i] = tempX[i];
		}
		

		//for (int i = 0; i < n; i++)
			//cout << x[i] << "\t";
		//for (int i = 0; i < n; i++)
			//cout << prevX[i] << "\t";
		//cout << endl;


		//Сравнение предыдущих значений x с новыми
		int flag = 0;
		for (int i = 0; i < n; i++)
		{
			if (prevX[i] >= x[i] - eps && prevX[i] <= x[i] + eps){
				flag++;
			}
		}
		if (flag == n && s > 0)
		{
			cout << "Количество итераций: " << s + 1<< endl;
			delete[] prevX;
			return x;
		}
		else
			flag = 1;
		for (int i = 0; i < n; i++)
			prevX[i] = x[i];
		s++;
	}
	return x;
}

int main() 
{
  double **a, *y, *x, *CH;
  int n, Sw;

  while (true){
    cout << "Ручной ввод(1) или чтение из файла(2):  ";
    cin >> Sw;
    switch (Sw) {
      case 1:


          cout << "Введите количество уравнений: ";
          cin >> n;
          a = new double*[n];
          y = new double[n];
          for (int i = 0; i < n; i++) 
          {
            a[i] = new double[n];
            for (int j = 0; j < n; j++) 
            {
              cout << "a[" << i << "][" << j << "]= ";
              cin >> a[i][j];
            }
          }
          for (int i = 0; i < n; i++) 
          {
            cout << "y[" << i << "]= ";
            cin >> y[i];
          }
          matrixPrint(a, y, n);
          cout << endl;
          CH = check(a, y, n);
          if (CH == NULL)
          {
          	cout << "ERR\n---------" << endl;

            continue;
          }
          x = zeidel(a, y, n);
             if (x == NULL) {
                cout << "ERR" << endl;
                continue;
              }
          for (int i = 0; i < n; i++)
            cout << endl <<"x[" << i << "]=" << x[i] << endl;
          delete[] x;
          delete[] y;
          break;



      case 2:
          for (int k=1; k<7; k++)
          {
            
            string path = to_string(k) + ".txt";
            ifstream in(path);
            if (in.is_open())
            {
              in >> n;
              a = new double*[n];
              for (int i = 0; i < n; i++)
              {
                a[i] = new double[n];
                for (int j = 0; j < n; j++)
                {  
                  in >> a[i][j];
                  
                }

              }
              y = new double[n];
              for (int i = 0; i < n; i++) 
              { 
                in >> y[i];
                
              }
              matrixPrint(a, y, n);
              cout << endl;
              CH = check(a, y, n);
              if (CH == NULL)
         	  {
          		cout << "ERR\n-------------------" << endl;
          		continue;
              }
              x = zeidel(a, y, n);
              if (x == NULL) {
                cout << "ERR" << endl;
                cout << "-------------------" << endl;
                continue;
              }
              	
           		for (int i = 0; i < n; i++) 
               		cout << endl <<"x[" << i << "]=" << x[i] << endl;            
            
            }

            else {
              cout << "Ошибка открытия файла";
            }
            in.close();
            cout << "-------------------" << endl;
            delete[] x;
            delete[] y;
          }
          break;
    }
  }

  return 0;
}