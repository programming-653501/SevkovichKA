#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "TernaryTree.h"


int main()
{
	TernaryTree tree;

	std::cout << "Input lines that you want to put into ternary tree.\n";
	std::cout << "Input empty line when done.\n\n";

	std::string temp_string = " ";

	while (temp_string != "")
	{
		std::getline(std::cin, temp_string);
		tree.Put(temp_string);
	}

	std::cout << "Tree depth: " << tree.GetDepth();

	_getch();
    return 0;
}

