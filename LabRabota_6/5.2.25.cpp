#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include "TernaryTree.h"

bool isLettersOnly(std::string pString);

int main()
{
	TernaryTree tree;

	std::cout << "Input lines that you want to put into ternary tree.\n";
	std::cout << "Input empty line when done.\n\n";

	std::string TempString;
	std::getline(std::cin, TempString);

	while (TempString != "")
	{
		if (isLettersOnly(TempString))
		{
			tree.Add(TempString);
		}
		else
		{
			std::cout << "Wrong input, try again: ";
		}

		std::getline(std::cin, TempString);
	}

	std::cout << "Tree depth: " << tree.GetDepth();

	_getch();
	return 0;
}

bool isLettersOnly(std::string pString)
{
	int StringSize = pString.size();

	for (size_t i = 0; i < StringSize; i++)
	{
		bool isUpperCase = (pString[i] >= 'A' && pString[i] <= 'Z');
		bool isLowerCase = (pString[i] >= 'a' && pString[i] <= 'z');

		if (!isLowerCase && !isUpperCase)
		{
			return false;
		}
	}

	return true;
}
