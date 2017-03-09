#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;

long long factorial(int);
void input(double&, double&, double&);
int find_n(double, double);
double sin_taylor(double, double);

int main() 
{
	setlocale(LC_ALL, "Russian");

	double number;
	double n;
	double epsilon;

	input(n, number, epsilon);

	cout << "\nЗначение через встроенную функцию равно " << sin(number) << endl;

	cout << "Значение через сумму ряда равно " << sin_taylor(n, number) << endl << endl;

	n = find_n(number, epsilon);

	cout << "Необходимое количество членов рядa: " << n << endl;
	cout << "Тогда значение через ряд будет равно " << sin_taylor(n, number);

	_getch();
	return 0;
}

void input(double& n, double& number, double& epsilon)
{
	cout << "Введите количество членов ряда: ";
	cin >> n;

	if (n <= 0 || (((int)n) != n))  
	{
		cout << "Неверный ввод. Нажмите любую клавишу для выхода.";
		_getch();
		exit(0);
	}

	cout << "Введите число: ";
	cin >> number;

	cout << "Введите погрешность: ";
	cin >> epsilon;

	if (epsilon <= 0)
	{
		cout << "Неверный ввод. Нажмите любую клавишу для выхода.";
		_getch();
		exit(0);
	}
}

int find_n(double number, double epsilon)
{
	int n = 0;
	double sin_taylor = 0;

	do
	{
		n++;
		sin_taylor += pow(-1, n + 1) * pow(number, 2 * n - 1) / factorial(2 * n - 1);
	
	} while (abs(sin_taylor - sin(number)) > epsilon);

	return n;
}

double sin_taylor(double n, double number)
{
	double sin_taylor = 0;

	for (; n > 0; n--) //Вычисление через ряд
	{
		sin_taylor += pow(-1, n - 1) * pow(number, 2 * n - 1) / factorial(2 * n - 1);
	}

	return sin_taylor;
}

long long factorial(int F) //Вычисление факториала
{ 
	return (F == 0) ? 1 : F * factorial(F - 1);
}
