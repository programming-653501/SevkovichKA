#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <iomanip>

int get_row();
int get_col();
void show_array(int**, int, int);
void fill_array(int**, int, int);
bool is_uint(char*);
int my_strlen(char*);

int main()
{
	setlocale(LC_ALL, "Rus");
	int row = get_row();
	int col = get_col();

	int** a = new int*[row];
	for (int i = 0; i < row; i++)
	{
		a[i] = new int[col];

		for (int j = 0; j < col; j++)
		{
			a[i][j] = 0;
		}
	}

	fill_array(a, row, col);

	show_array(a, row, col);

	for (int i = 0; i < row; i++)
	{
		delete[] a[i];
	}
	delete[] a;

	std::cout << "\nНажмите любую клавишу для выхода.";

	_getch();
	return 0;
}


int get_row()
{
	char row_ch[10];

	std::cout << "Введите количество строк: ";

	while (true)
	{
		std::cin.getline(row_ch, 10);

		if (is_uint(row_ch))
		{
			break;
		}

		std::cout << "Неверный ввод, попробуйте ещё раз: ";
	}

	return atoi(row_ch);
}

int get_col()
{
	char col_ch[10];

	std::cout << "Введите количество столбцов: ";

	while (true)
	{
		std::cin.getline(col_ch, 10);

		if (is_uint(col_ch))
		{
			break;
		}

		std::cout << "Неверный ввод, попробуйте ещё раз: ";
	}

	return atoi(col_ch);
}

void show_array(int **a, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			std::cout << std::setw(4) << a[i][j];
		}
		std::cout << std::endl;
	}
}

void fill_array(int **a, int row, int col)
{
	int row_ = 0;
	int col_ = 0;
	int i = 1;
	int side = 0;

	while (i <= row*col)
	{
		switch (side % 4)
		{
		case 0:
			for (; col_ < col && a[row_][col_] == 0; col_++)
			{
				a[row_][col_] = i;
				i++;
			}
			col_--;
			row_++;
			break;
		case 1:
			for (; row_ < row && a[row_][col_] == 0; row_++)
			{
				a[row_][col_] = i;
				i++;
			}
			row_--;
			col_--;
			break;
		case 2:
			for (; col_ >= 0 && a[row_][col_] == 0; col_--)
			{
				a[row_][col_] = i;
				i++;
			}
			col_++;
			row_--;
			break;
		case 3:
			for (; row_ >= 0 && a[row_][col_] == 0; row_--)
			{
				a[row_][col_] = i;
				i++;
			}
			row_++;
			col_++;
			break;
		}

		side++;
	}
}

bool is_uint(char *str)
{
	int length = my_strlen(str);

	for (int i = 0; i < length; i++)
	{
		if (str[i] < 48 || str[i] > 57)
		{
			return false;
		}
	}
	return true;
}

int my_strlen(char *str)
{
	int i = 0;

	while (str[i + 1] != '\0')
	{
		i++;
	}

	return i;
}