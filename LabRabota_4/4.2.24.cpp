// 4.2.24.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

std::string input();
void find_in_file(std::string);
std::string read_word();
bool same_letters(std::string, std::string);
bool is_one_word(std::string);
int my_strlen(std::string);
std::string my_tolower(std::string str);

int count = 0;
std::fstream file;

int main()
{
	std::string path = "D:\\dictionary.txt"; //you can store here path to the dictionary file
	file.open(path, std::ios::in);

	if (file.fail())
	{
		std::cout << "File does not exist!";
	}
	else
	{
		std::string str = input();

		find_in_file(str);

		if (count == 0)
		{
			std::cout << "There are no such words in a file!";
		}
		else
		{
			std::cout << "\n\nAll words were found!";
		}

	}
	
	std::cout << "\nPress any button to exit.";
	file.close();
	_getch();
	return 0;
}

std::string input()
{
	std::string str;

	std::cout << "It will take some time to found all words, be patience.\n";
	std::cout << "Input a single word: ";

	while (true)
	{
		std::getline(std::cin, str);

		if (is_one_word(str))
		{
			str = my_tolower(str);
			return str;
		}

		std::cout << "Wrong input, try again: ";
	}

	return std::string();
}

void find_in_file(std::string input_word)
{
	while (!file.eof())
	{
		std::string file_word = read_word();

		if (same_letters(file_word, input_word))
		{
			std::cout << file_word << '\n';
			count++;
		}
	}
}

std::string read_word()
{
	std::string str = "";

	while (true)
	{
		char temp;

		file.get(temp);

		if (file.eof() || temp == ' ' || temp == '\n')
		{
			break;
		}

		str += temp;
	}

	return str;
}

bool same_letters(std::string str1, std::string str2)
{
	for (size_t i = 0; i < str1.length(); i++)
	{
		bool a = false;

		for (size_t k = 0; k < str2.length(); k++)
		{
			if (str1[i] == str2[k])
			{
				a = true;
				break;
			}
		}

		if (a == false)
		{
			return a;
		}
	}

	return true;
}

bool is_one_word(std::string str)
{
	for (int i = 0; i < my_strlen(str); i++)
	{
		if (str[i] == ' ' || ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z')))
		{
			return false;
		}
	}

	return true;
}

int my_strlen(std::string str)
{
	for (int i = 0; ; i++)
	{
		if (str[i] == '\0')
		{
			return i;
		}
	}
}

std::string my_tolower(std::string str)
{
	for (size_t i = 0; i < my_strlen(str); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}

	return str;
}