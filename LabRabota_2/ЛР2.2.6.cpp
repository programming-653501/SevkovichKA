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

	cout << "\n�������� ����� ���������� ������� ����� " << sin(number) << endl;

	cout << "�������� ����� ����� ���� ����� " << sin_taylor(n, number) << endl << endl;

	n = find_n(number, epsilon);

	cout << "����������� ���������� ������ ���a: " << n << endl;
	cout << "����� �������� ����� ��� ����� ����� " << sin_taylor(n, number);

	_getch();
	return 0;
}

void input(double& n, double& number, double& epsilon)
{
	cout << "������� ���������� ������ ����: ";
	cin >> n;

	if (n <= 0 || (((int)n) != n))  
	{
		cout << "�������� ����. ������� ����� ������� ��� ������.";
		_getch();
		exit(0);
	}

	cout << "������� �����: ";
	cin >> number;

	cout << "������� �����������: ";
	cin >> epsilon;

	if (epsilon <= 0)
	{
		cout << "�������� ����. ������� ����� ������� ��� ������.";
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

	for (; n > 0; n--) //���������� ����� ���
	{
		sin_taylor += pow(-1, n - 1) * pow(number, 2 * n - 1) / factorial(2 * n - 1);
	}

	return sin_taylor;
}

long long factorial(int F) //���������� ����������
{ 
	return (F == 0) ? 1 : F * factorial(F - 1);
}
