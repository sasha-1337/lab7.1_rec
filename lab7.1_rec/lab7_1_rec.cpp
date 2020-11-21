#include <iostream>
#include <iomanip>
#include <time.h>
#include <Windows.h>

using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
	a[i][j] = Low + rand() % (High - Low + 1);

	if (j < colCount - 1)
		Create(a, rowCount, colCount, Low, High, i, j + 1);
	else
	if (i < rowCount - 1)
		Create(a, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** a, const int rowCount, const int colCount, int i, int j)
{
	cout << setw(4) << a[i][j];
	if (j < colCount - 1)
		Print(a, rowCount, colCount, i, j + 1);
	else
		if (i < rowCount - 1) 
		{
			cout << endl;
			Print(a, rowCount, colCount, i + 1, 0);
		}
		else 
			cout << endl << endl;
}

void Change(int** a, const int row1, const int row2, const int colCount, int j)
{
	int tmp;
	tmp = a[row1][j];
	a[row1][j] = a[row2][j];
	a[row2][j] = tmp;
	if (j < colCount - 1) {
		Change(a, row1, row2, colCount, j + 1);
	}
}

void Sort(int** a, const int rowCount, const int colCount, int i0, int i1)
{
	if (i1 < rowCount - i0 - 1) {
		if ((a[i1][0] > a[i1 + 1][0])
			||
			(a[i1][0] == a[i1 + 1][0] &&
				a[i1][1] > a[i1 + 1][1])
			||
			(a[i1][0] == a[i1 + 1][0] &&
				a[i1][1] == a[i1 + 1][1] &&
				a[i1][3] < a[i1 + 1][3]))
			Change(a, i1, i1 + 1, colCount, 0);
			Sort(a, rowCount, colCount, i0, i1 + 1);
	}
	else
		if (i0 < rowCount - 1)
			Sort(a, rowCount, colCount, i0 + 1, 0);
		 
			
}

int Calc(int** a, const int rowCount, const int colCount, int i, int j, int &S, int &t)
{
	if (!(a[i][j] % 2))
	{
		S += a[i][j];
		t++;
		a[i][j] = 0;
	}
	if (j < colCount - 1) 
			return a[i][j] + Calc(a, rowCount, colCount, i, j + 1, S, t);
	else
		if (i < rowCount - 1) 
				return a[i][j] + Calc(a, rowCount, colCount, i + 1, 0, S, t);
		else 
			return a[i][j];
	return t;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	int Low = -12;
	int High = 23;

	int rowCount = 7;
	int colCount = 6;

	int** a = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		a[i] = new int[colCount];

	cout << " Матриця: " << endl;
	Create(a, rowCount, colCount, Low, High,0,0);
	Print(a, rowCount, colCount,0,0);
	cout << " Відсортована матриця: " << endl;
	Sort(a, rowCount, colCount,0,0);
	Print(a, rowCount, colCount,0,0);

	int t = 0;
	int S = 0;
	cout << " Матриця тільки з непарними елементами: " << endl;
	Calc(a, rowCount, colCount, 0, 0, S, t);
	Print(a, rowCount, colCount,0,0);
	cout << " S = " << S << endl;
	cout << " Кількість: " << t << endl;
	
	

	for (int i = 0; i < rowCount; i++)
		delete[] a[i];
	delete[] a;

	system("pause");
	return 0;
}