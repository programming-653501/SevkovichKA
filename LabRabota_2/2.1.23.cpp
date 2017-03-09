#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>

const int AMOUNT_OF_FIELDS = 3;
const int AMOUNT_OF_FRUITS = 3;

enum fields { COST, WEIGHT, COST_PER_KG };
enum friuts { MANDARINS, PEACHES, GRAPES };

int menu_and_choise();
void make_order(double&, double&, const double);
void show_cart(double info[AMOUNT_OF_FIELDS][AMOUNT_OF_FRUITS]);
void calculate_cost(double info[AMOUNT_OF_FIELDS][AMOUNT_OF_FRUITS]);
void feedback();
bool is_udouble(std::string);

int main()
{
	std::cout << "Welcome to eFruit!";

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
			std::cout << "\nThanks for choosing eFruit!";
			std::cout << "\nPress any button to exit.";
			_getch();
			return 0;
		}

		}
	}
}

int menu_and_choise()
{
	int choise;

	std::cout << "\nYou are in menu.\nChoose what to do.\n\n" <<
		"1) Order mandarins\n2) Order peaches\n3) Order grapes\n" <<
		"4) Show cart\n5) Calculate price\n6) Feedback\n0) Exit\n";

	while (true)
	{
		choise = _getch() - 48;

		if (choise >= 0 && choise < 7)
		{
			break;
		}

		std::cout << "\nWrong input! Try again: ";
	}

	std::cout << "\nYour choise: " << choise << std::endl;

	return choise;
}

void make_order(double &cost, double &weight, const double cost_per_kg)
{
	double weight_temp;

	std::cout << "\nInput 0 to return to the menu.";
	std::cout << "\nHow mane kilos do you want to order: ";

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

		std::cout << "\nWrong input! Try again: ";
	}

	weight += weight_temp;

	cost += weight_temp * cost_per_kg;

	std::cout << "\nYour order is accepted!";
	std::cout << "\nPress any button to return to the menu.\n\n";
	_getch();
}

void show_cart(double info[AMOUNT_OF_FIELDS][AMOUNT_OF_FRUITS])
{
	std::cout << std::setprecision(2) << std::fixed;

	std::cout << "\nYou ordered:\n";

	std::cout << "Mandarins: " << info[WEIGHT][MANDARINS] << " kg, total cost  $" 
		<< info[COST][MANDARINS] << std::endl;

	std::cout << "Peaches: " << info[WEIGHT][PEACHES] << " kg, total cost  $"
		<< info[COST][PEACHES] << std::endl;

	std::cout << "Grapes: " << info[WEIGHT][GRAPES] << " kg, total cost  $"
		<< info[COST][GRAPES] << std::endl;

	std::cout << std::endl << "\nPress any button to return to the menu.\n\n";

	_getch();
}

void calculate_cost(double info[AMOUNT_OF_FIELDS][AMOUNT_OF_FRUITS])
{
	double total_cost = 0;
	double total_weight = 0;

	for (int i = MANDARINS; i < AMOUNT_OF_FRUITS; i++) //Ïîäñ÷¸ò îáùåé ñòîèìîñòè è îáùåãî âåñà
	{
		total_cost += info[COST][i];
		total_weight += info[WEIGHT][i];
	}

	if (0 == total_cost)
	{
		std::cout << "Your cart is empty!";
		std::cout << "\nPress any button to return to the menu.\n\n";
		_getch();
		return;
	}

	std::cout << "\n10% discount for $100 order";

	if (total_cost >= 100) //Ïîäñ÷¸ò ñêèäêè
	{
		std::cout << "(+)" << std::endl;
		total_cost *= 0.9;
	}
	else
	{
		std::cout << "(-)" << std::endl;
	}

	std::cout << "Delivery cost: ";

	if (total_weight < 5) //Ïîäñ÷¸ò ñòîèìîñòè äîñòàâêè
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

	std::cout << "Total order cost $" << total_cost << std::endl;

	std::cout << "\nPress any button to return to the menu.\n\n";
	_getch();
}

void feedback()
{
	std::cout << "\neFruit\nLicense 735926861122.\nPhone for information +375291234567";

	std::cout << "\nPress any button to return to the menu.\n\n";

	_getch();
}

bool is_udouble(std::string d_num)
{
	for (int i = 0; i < d_num.length(); i++)
	{
		if ((d_num[i] < '0' || d_num[i] > '9') && (d_num[i] != '.'))
		{
			return false;
		}
	}

	return true;
}
