#include "stdafx.h"
#include <iomanip>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>

int my_strlen(std::string);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "Input lines. Input empty line when you want to over:\n\n";

	std::vector <std::string> lines(0);

	bool again = true;
	int line_length = 0;

	while (again)
	{
		std::string temp_str;
		std::getline(std::cin, temp_str);
		
			if (temp_str == "")
		{
			again = false;
		}
		else
		{
			lines.push_back(temp_str);

			if (line_length < my_strlen(temp_str))
			{
				line_length = my_strlen(temp_str);
			}

			for (int k = 0; k < lines.size(); k++)
			{
				if (my_strlen(lines[k]) < line_length)
				{
					while (my_strlen(lines[k]) <= line_length)
					{
						lines[k] += ' ';
					}
					
					while (lines[k][line_length] == ' ')
					{
						for (int i = 1; i < line_length; i++)
						{
							int m = 1;

							if (i < line_length && lines[k][i] == ' ' && lines[k][i - m] != ' ' && lines[k][line_length] == ' ')
							{
								for (int l = line_length; l > i; l--)
								{
									lines[k][l] = lines[k][l - 1];
								}

								lines[k][i] = ' ';
								i++;
							}
							
							m++;
						}
					}
				}
			}
		}
	}

	for (std::string i : lines)
	{
		std::cout << i << '\n';
	}

	_getch();
	return 0;
}

int my_strlen(std::string str)
{
	int i = 0;

	while (str[i + 1] != '\0')
	{
		i++;
	}

	return i;
}