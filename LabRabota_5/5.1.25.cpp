#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "DynamicStack.h"

void menu();
void push(DynamicStack&);
bool is_udouble(std::string d_num);

int main()
{
	menu();

	std::cout << "Goodbye! Press any button.";
	_getch();
	return 0;
}

void menu()
{
	DynamicStack Stack;
	while (true)
	{
		std::cout << "You are in menu.\n";
		std::cout << "1) Add element to stack\n";
		std::cout << "2) Get element from stack\n";
		std::cout << "3) Reverse stack\n";
		std::cout << "0) Quit\n";
		std::cout << "Your choise: ";

		int ch;

		while (true)
		{
			ch = _getch() - 48;
			std::cout << static_cast<char>(ch + 48) << '\n';

			if (ch >= 0 && ch <= 3)
			{
				break;
			}

			std::cout << "Wrong input, try again: ";
		}

		try
		{
			std::cout << "\n\n";

			switch (ch)
			{
			case 1:
				push(Stack);
				std::cout << "\nElement was successfully added!";
				break;
			case 2:
				std::cout << "Received element is: " << Stack.pop();
				break;
			case 3:
				Stack.Reverse();
				std::cout << "\nStack was successfully reversed!";
				break;
			case 0:
				return;
			}

			std::cout << "\n\n";
		}
		catch (std::string Empty)
		{
			std::cout << Empty;
		}
		
		std::cout << "Press any button to exit to the menu.\n\n\n";
		_getch();
	}
}

void push(DynamicStack& Stack)
{
	std::cout << "Input value you want to add to the stack: ";

	std::string temp;

	while (true)
	{
		std::getline(std::cin, temp);

		if (is_udouble(temp))
		{
			Stack.push(atof(temp.c_str()));
			return;
		}
		
		std::cout << "Wrong input, try again: ";
	}
}

bool is_udouble(std::string d_num)
{
	if (d_num.length() == 0)
	{
		return false;
	}

	for (size_t i = 0; i < d_num.length(); i++)
	{
		if ((d_num[i] < '0' || d_num[i] > '9') && (d_num[i] != '.'))
		{
			return false;
		}
	}

	return true;
}