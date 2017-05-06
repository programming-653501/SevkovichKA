#pragma once

#include "Date.h"
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>

struct Employee
{
	std::string Name;
	Date BirthDate;
	std::string PassportNumber;
	std::string SocialSecurityNumber;
	std::string Education;
	std::string Position;
	double Salary;
	Date StartWork;
	std::vector<std::string> Notes;
	bool AtVacationStatus;

	void SetName()
	{
		bool again = true;
		std::string tempString;

		std::cout << "Input name (nothing but the latin letters is allowed):\n";

		while (again)
		{
			getline(std::cin, tempString);

			bool correct = (tempString.size() > 0);

			for (size_t i = 0; i < tempString.length(); i++)
			{
				bool IsUpperCase = (tempString[i] >= 'A' && tempString[i] <= 'Z');
				bool IsLowerCase = (tempString[i] >= 'a' && tempString[i] <= 'z');
				bool IsWhitespace = (tempString[i] == ' ');

				if (!(IsUpperCase || IsLowerCase || IsWhitespace))
				{
					correct = false;
					break;
				}
			}

			if (!correct)
			{
				std::cout << "Wrong input, try again: ";
			}
			else
			{
				again = false;
			}
		}

		std::cout << '\n';

		this->Name = tempString;
	}

	void SetBirthDate()
	{
		std::cout << "Input date of birth (mm/dd/yyyy): ";

		std::string pDate;

		while (true)
		{
			getline(std::cin, pDate);

			if (Date::IsDateStringValid(pDate))
			{
				Date temp(pDate);
				Date today = Date::GetCurrentDate();

				if (today - temp > 0)
				{
					std::cout << "Date of birth can not be after today\n";
				}
				else
				{
					this->BirthDate.Set(pDate);
					break;
				}
			}

			std::cout << "Wrong input, try again (mm/dd/yyyy): ";
		}

		std::cout << '\n';
	}

	void SetPassportNumber()
	{
		bool again = true;
		std::string tempString;

		std::cout << "Input passport number (nothing but the capital latin letters and numbers allowed):\n";

		while (again)
		{
			getline(std::cin, tempString);

			bool correct = (tempString.size() > 0);

			for (size_t i = 0; i < tempString.length(); i++)
			{
				bool IsUpperCase = (tempString[i] >= 'A' && tempString[i] <= 'Z');
				bool IsDigit = (tempString[i] >= '0' && tempString[i] <= '9');

				if (!(IsUpperCase || IsDigit))
				{
					correct = false;
					break;
				}
			}

			if (!correct)
			{
				std::cout << "Wrong input, try again: ";
			}
			else
			{
				again = false;
			}
		}

		std::cout << '\n';

		this->PassportNumber = tempString;
	}

	void SetSocialSecurityNumber()
	{
		bool again = true;
		std::string tempString;

		std::cout << "Input social security number (9 numbers):";

		while (again)
		{
			getline(std::cin, tempString);

			bool correct = true;

			if (tempString.length() != 9)
			{
				correct = false;
			}
			else
			{
				for (size_t i = 0; i < tempString.length(); i++)
				{
					if (!(tempString[i] >= '0' && tempString[i] <= '9'))
					{
						correct = false;
						break;
					}
				}
			}

			if (!correct)
			{
				std::cout << "Wrong input, try again: ";
			}
			else
			{
				again = false;
			}
		}

		std::cout << '\n';

		this->SocialSecurityNumber = tempString;
	}

	void SetEducation()
	{
		std::string tempString;

		std::cout << "Input education (empty line if none): ";

		getline(std::cin, tempString);

		std::cout << '\n';

		this->Education = tempString;
	}

	void SetPosition()
	{
		bool again = true;
		std::string tempString;

		std::cout << "Input position (nothing but the latin letters and whitespaces is allowed):\n";

		while (again)
		{
			getline(std::cin, tempString);

			bool correct = (tempString.size() > 0);

			for (size_t i = 0; i < tempString.length(); i++)
			{
				bool IsUpperCase = (tempString[i] >= 'A' && tempString[i] <= 'Z');
				bool IsLowerCase = (tempString[i] >= 'a' && tempString[i] <= 'z');
				bool IsWhitespace = (tempString[i] == ' ');

				if (!(IsUpperCase || IsLowerCase || IsWhitespace))
				{
					correct = false;
					break;
				}
			}

			if (!correct)
			{
				std::cout << "Wrong input, try again: ";
			}
			else
			{
				again = false;
			}
		}

		std::cout << '\n';

		this->Position = tempString;
	}

	void SetSalary()
	{
		bool again = true;
		bool correct;

		std::string tempString;

		std::cout << "Input salary in dollars and cents (dollars.cents, accuracy up to a cent)\n(nothing but the numbers and dot is allowed):";

		while (again)
		{
			correct = true;

			getline(std::cin, tempString);

			std::vector<std::string> DollarsCents = Date::SplitString(tempString, '.');

			if (DollarsCents.size() == 2)
			{
				std::string dollars = DollarsCents[0];
				std::string cents = DollarsCents[1];

				if (dollars.length() > 0 && cents.length() == 2)
				{
					for (size_t i = 0; i < tempString.length(); i++)
					{
						bool IsDot = (tempString[i] == '.');
						bool isDigit = (tempString[i] >= '0' && tempString[i] <= '9');

						if (!isDigit && !IsDot)
						{
							correct = false;
							break;
						}
					}
				}
				else
				{
					correct = false;
				}
			}
			else
			{
				correct = false;
			}

			if (!correct)
			{
				std::cout << "Wrong input, try again: ";
			}
			else
			{
				again = false;
			}
		}

		std::cout << '\n';

		this->Salary = atof(tempString.c_str());
	}

	void SetStartWork()
	{
		std::cout << "Input date of work start (mm/dd/yyyy):";

		std::string pDate;

		while (true)
		{
			getline(std::cin, pDate);

			if (Date::IsDateStringValid(pDate))
			{
				this->StartWork.Set(pDate);
				break;
			}
			else
			{
				std::cout << "Wrong input, try again (mm/dd/yyyy): ";
			}
		}

		std::cout << '\n';
	}

	void SetNotes()
	{
		bool again = true;

		std::cout << "Input notes (each one on the new line, input empty line when done):\n";

		while (again)
		{
			std::string tempString;
			getline(std::cin, tempString);

			if (tempString == "")
			{
				again = false;
			}
			else
			{
				this->Notes.push_back(tempString);
			}
		}

		std::cout << '\n';
	}

	void SetStatus()
	{
		std::string tempString;

		std::cout << "Input employee status (only number: 1 - working, 2 - at vacation): ";

		while (true)
		{
			getline(std::cin, tempString);

			if (tempString.size() == 1 && (tempString[0] == '1' || tempString[0] == '2'))
			{
				break;
			}

			std::cout << "Wrong input, try again: ";
		}

		std::cout << '\n';

		this->AtVacationStatus = atoi(tempString.c_str());
	}
};