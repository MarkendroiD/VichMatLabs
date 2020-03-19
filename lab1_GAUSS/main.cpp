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
double * gauss(double **a, double *y, int n) 
{

  double *x, max;
  int k, index;
  const double eps = 0.0001;
  x = new double[n];
  k = 0;
  if (n == 1){
    if(a[0][0] == 0 && y[0] == 0)
      cout << "Бесконечное кол-во решений" << endl;
  delete[] a;
  delete[] y;
  return NULL;
  }


  //matrixPrint(a, y, n);
  //cout << endl;
  int flag = 0, flag1 = 0;
  while (k < n) 
  {
	max = abs(a[0][0]);
	index = k;
  	for (int i = k; i < n; i++) 
  	{
    	if (abs(a[i][k]) > max)
    	{
      		max = abs(a[i][k]);
      		index = i;
    	}
  	}
  // Перестановка строк
  	if (max != abs(a[k][k]))
  	{
		for (int j = k; j < n; j++) 
		{
		double temp = a[k][j];
		a[k][j] = a[index][j];
		a[index][j] = temp;

		}
	}
	matrixPrint(a, y, n);
	cout << endl;
	double temp = y[k];
	y[k] = y[index];
	y[index] = temp;
    for (int i = 0; i < n; i++)
    {
		for (int j = 0; j < n; j++)
		{
        
		    if (abs(a[i][j]) < eps)
		      flag++;
		    if (flag == n)
		    {
		    	flag1++;
		    	if (y[i] != 0)
		    	{
			        cout << "Система уравнений не совместна (решений нет)" << endl;
			        delete[] a;
			        delete[] y;
			        return NULL;
		        }
		    }
		}
      flag = 0;
    }
    if (flag1 == n-1 && flag1 != 0){
    	cout << "Бесконечное кол-во решений" << endl;
		delete[] a;
		delete[] y;
		return NULL;
    }
    flag1 = 0;
    for (int i = k; i < n; i++) 
    {
	//matrixPrint(a, y, n);
	//cout << endl;
	double temp = a[i][k];
	if (abs(temp) < eps) continue;
	for (int j = 0; j < n; j++) 
		a[i][j] = a[i][j] / temp;
	y[i] = y[i] / temp;

	if (i == k)  continue;
	for (int j = 0; j < n; j++)
		a[i][j] = a[i][j] - a[k][j];
	y[i] = y[i] - y[k];
    }
    for (int i = 0; i < n; i++)
    {
		for (int j = 0; j < n; j++)
		{
			int h = a[i][j] * (10.0/eps);
			if (h % 10 >= 5) 
			{
				h+=10;
        	}
			h = h/10;
			a[i][j] = (double)h  * eps;
			int l = y[i] * (10.0/eps);
			if (l % 10 >= 5) {
				l+=10;
			}
			l = l/10;
			y[i]= (double)l  * eps;
		}
	}
    //matrixPrint(a, y, n);
    //cout << endl;
    k++;

	}
	double t[n-1];
	for (int l = 0;l <= n-1; l++){
		t[l] = y[l]	;
	}
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = t[k];
		for (int i = 0; i < k; i++)
			t[i] = t[i] - a[i][k] * x[k];
	}

    //matrixPrint(a, y, n);
    //cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int h = a[i][j] * (10.0/eps);
			if (h % 10 >= 5) 
			{
				h+=10;
			}
			h = h/10;
			a[i][j] = (double)h  * eps;
			int l = y[i] * (10.0/eps);
			if (l % 10 >= 5) 
			{
				l+=10;
			}
			l = l/10;
			y[i]= (double)l  * eps;
		}
	}
    //matrixPrint(a, y, n);
    //cout << endl;
	for (int i = 0; i < n; i++){
		int h = x[i] * (10.0/eps);
		if (h % 10 >= 5) 
		{
		  h+=10;
		}
		h = h/10;
		x[i]= (double)h * eps;
	}
  return x;
}

int main() 
{
  double **a, *y, *x;
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
          x = gauss(a, y, n);
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
          for (int k=1; k<6; k++)
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
              x = gauss(a, y, n);
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