#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>

const int AMOUNT_OF_FIELDS = 3;
const int AMOUNT_OF_FRUITS = 3;

enum fields { COST, WEIGHT, COST_PER_KG };
enum friuts { MANDARINS, PEACHES, GRAPES};

int menu_and_choise();
void make_order(double&, double&, const double);
void show_cart(double info[AMOUNT_OF_FIELDS][AMOUNT_OF_FRUITS]);
void calculate_cost(double info[AMOUNT_OF_FIELDS][AMOUNT_OF_FRUITS]);
void feedback();
bool is_udouble(std::string);

int main()
{
	setlocale(LC_ALL, "Rus");
	
	std::cout << "Добро пожаловать в магазин eFruit!";

	double info[AMOUNT_OF_FIELDS][AMOUNT_OF_FRUITS] = {};

	info[COST_PER_KG][MANDARINS] = 1.14;
	info[COST_PER_KG][PEACHES] = 1.00;
	info[COST_PER_KG][GRAPES] = 1.28;

	while (true)
	{
		int choise = menu_and_choise();

		switch (choise)
		{
			case 1:
			{
				make_order(info[COST][MANDARINS], info[WEIGHT][MANDARINS],
					info[COST_PER_KG][MANDARINS]);
				break;
			}

			case 2:
			{
				make_order(info[COST][PEACHES], info[WEIGHT][PEACHES],
					info[COST_PER_KG][PEACHES]);
				break;
			}

			case 3:
			{
				make_order(info[COST][GRAPES], info[WEIGHT][GRAPES],
					info[COST_PER_KG][GRAPES]);
				break;
			}
			
			case 4:
			{
				show_cart(info);
				break;
			}

			case 5:
			{
				calculate_cost(info);
				break;
			}
			
			case 6:
			{
				feedback();
				break;
			}
			
			case 0:
			{
				std::cout << "\nСпасибо, что выбрали магазин eFruit!";
				std::cout << "\nНажмите любую клавишу для выхода.";
				_getch();
				return 0;
			}
			
		}
	}
}

int menu_and_choise()
{
	int choise;

	std::cout << "\nВы в меню.\nВыбирите, что делать дальше.\n\n" <<
		"1) Заказать мандарины\n2) Заказать персики\n3) Заказать виноград\n" <<
		"4) Показать корзину\n5) Расчёт стоимости заказа\n6) Обратная связь\n0) Выход\n";

	while (true)
	{
		choise = _getch() - 48;

		if (choise >= 0 && choise < 7)
		{
			break;
		}

		std::cout << "\nНеверный ввод! Введите ещё раз: ";
	}

	std::cout << "\nВы выбрали: " << choise << std::endl;

	return choise;
}

void make_order(double &cost, double &weight, const double cost_per_kg)
{
	double weight_temp;

	std::cout << "\nВведите 0 чтобы вернуться обратно в меню.";
	std::cout << "\nСколько килограмм вы хотите заказать?\nДробную часть отделяйте от целой запятой\nЗаказать: ";

	while (true)
	{
		std::string temp;

		std::getline(std::cin, temp);

		if (is_udouble(temp))
		{
			weight_temp = atof(temp.c_str());

			if (weight_temp == 0)
			{
				return;
			}

			if (weight_temp > 0)
			{
				break;
			}
		}

		std::cout << "\nНеверный ввод! Введите ещё раз: ";
	}

	weight += weight_temp;
	
	cost += weight_temp * cost_per_kg;

	std::cout << "\nВаш заказ принят!";
	std::cout << "\nНажмите любую клавишу для выхода в меню.\n\n";
	_getch();
}

void show_cart(double info[AMOUNT_OF_FIELDS][AMOUNT_OF_FRUITS])
{
	std::cout << std::setprecision(2) << std::fixed;

	std::cout << "\nВы наказали:\n";

	std::cout << "Мандарины: " << info[WEIGHT][MANDARINS] << " кг стоимостью "
		<< "$" << info[COST][MANDARINS] << std::endl;

	std::cout << "Персики: " << info[WEIGHT][PEACHES] << " кг стоимостью "
		<< "$" << info[COST][PEACHES] << std::endl;
	
	std::cout << "Виноград: " << info[WEIGHT][GRAPES] << " кг стоимостью "
		<< "$" << info[COST][GRAPES] << std::endl;
	
	std::cout << std::endl << "\nНажмите любую клавишу для выхода в меню.\n\n";
	
	_getch();
}

void calculate_cost(double info[AMOUNT_OF_FIELDS][AMOUNT_OF_FRUITS])
{
	double total_cost = 0;
	double total_weight = 0;

	for (int i = MANDARINS; i < AMOUNT_OF_FRUITS; i++) //Подсчёт общей стоимости и общего веса
	{
		total_cost += info[COST][i];
		total_weight += info[WEIGHT][i];
	}

	if (0 == total_cost)
	{
		std::cout << "Ваша корзина пуста!";
		std::cout << "\nНажмите любую клавишу для выхода в меню.\n\n";
		_getch();
		return;
	}

	std::cout << "\nСкидка 10% за заказ от $100 ";

	if (total_cost >= 100) //Подсчёт скидки
	{
		std::cout << "(+)" << std::endl;
		total_cost *= 0.9;
	}
	else 
	{
		std::cout << "(-)" << std::endl;
	}

	std::cout << "Стоимость доставки: ";

	if (total_weight < 5) //Подсчёт стоимости доставки
	{
		std::cout << "1$" << std::endl;
		total_cost += 1;
	}
	else if (total_weight < 20)
	{
		std::cout << "3$" << std::endl;
		total_cost += 3;
	}
	else
	{
		int extra = ((total_weight - 20) + 1) * 2 + 10;
		std::cout << std::setprecision(2) << extra << "$" << std::endl;
		total_cost += extra; 
	}

	std::cout << "Общая стоимость заказа $" << total_cost << std::endl;

	std::cout << "\nНажмите любую клавишу для выхода в меню.\n\n";
	_getch();
}

void feedback()
{
	std::cout << "\nМагазин eFruit\nЛицензия №735926861122.\nТелефон для справок +375291234567";

	std::cout << "\nНажмите любую клавишу для выхода в меню.\n\n";

	_getch();
}

bool is_udouble(std::string d_num)
{
	for (int i = 0; i < d_num.length(); i++)
	{
		if ((d_num[i] < '0' || d_num[i] > '9') && (d_num[i] != ','))
		{
			return false;
		}
	}

	return true;
}