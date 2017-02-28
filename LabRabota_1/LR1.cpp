#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");

	int nums[10][3];
	int num[3];
	int cnt = 0;
	bool all_found = false;

	for (num[0] = 1; cnt < 10; num[0]++)
	{
		for (num[1] = 1; num[1] <= 100; num[1]++)
		{
			for (num[2] = 1; num[2] <= 100; num[2]++)
			{
				if ((num[0] * num[0] + num[1] * num[1]) == (num[2] * num[2]))
				{
					bool already_found = false;
					//Проверка, не найдена ли уже такая  
					//тройка (например 3 4 5 и 4 3 5)
					for (int i = 0; i < cnt; i++) 
					{
						if (num[0] == nums[i][1] && num[1] == nums[i][0])
						{
							already_found = true;
						}
					}

					if (already_found)
					{
						break;
					}

					for (int i = 0; i < 3; i++)
					{
						nums[cnt][i] = num[i];
					}

					cout << num[0] << " " << num[1] << " " << num[2] << endl;

					cnt++;

					if (cnt == 10)
					{
						all_found = true;
						break;
					}
				}
			}

			if (all_found)
			{
				break;
			}
		}

		if (all_found)
		{
			break;
		}
	}


	_getch();
    return 0;
}

