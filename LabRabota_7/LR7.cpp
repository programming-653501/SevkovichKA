#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include "Employee.h"
#include "ListEmployee.h"
#include "Date.h"

using std::cin;
using std::cout;
using std::getline;
using std::string;
using std::fstream;
using std::vector;

void GetDataFromFile();			
void Menu();				
void MenuSearch();			
void AddEmployee();			
void RemoveEmployee();				
void ShowAllEmployees();
void CorrectEmployeeInfo();			
void ShowBirthdays();
void DismissalOrder();
void InputInfo(Employee &pEmployee, int pFieldChoise);
void WriteNewDataToFile();			
vector<int> FindEmployees(int pChoise);
bool IsUnsignedDouble(string pString);	
bool IsUnsignedInt(string pString);		
int GetOption(int pLow, int pHigh);		
void ShowEmployeeInfo(Employee pEmployee);

ListEmployee list;
string filePath = "D:\\MyProgramFiles\\EmployeesData.txt";	//path to data file
string dismissalOrderPath = "D:\\MyProgramFiles\\";			//path to dismissal order file

int main()
{
	cout << "Welcome!\n";
	cout << "Today: " << Date::GetCurrentDate().GetAsString() + '\n';

	try
	{
		GetDataFromFile();
	}
	catch (string FileNotExist)
	{
		cout << FileNotExist;

		fstream file(filePath, std::ios::out);
		file.close();

		file.open(filePath, std::ios::in);

		cout << "File was created.\n\n";
	}

	Menu();

	WriteNewDataToFile();

	cout << "\nPress any to exit.";
	_getch();
    return 0;
}

void GetDataFromFile()
{
	fstream file(filePath, std::ios::in);

	if (!file)
	{
		string FileNotExist = "File does not exist.\n";
		throw FileNotExist;
	}

	while (true)
	{
		if (file.eof())
		{
			break;
		}


		string tempString;
		Employee tempEmployee;

		// get name from file
		getline(file, tempEmployee.Name, '\n');

		// get birthdate from file
		getline(file, tempString, '\n');
		tempEmployee.BirthDate.Set(tempString);

		// get passport number
		getline(file, tempEmployee.PassportNumber, '\n');

		// get social security number
		getline(file, tempEmployee.SocialSecurityNumber, '\n');

		// get education
		getline(file, tempEmployee.Education, '\n');

		// get position
		getline(file, tempEmployee.Position, '\n');

		// get salary
		getline(file, tempString, '\n');
		tempEmployee.Salary = atof(tempString.c_str());

		// get begin work
		getline(file, tempString, '\n');
		tempEmployee.StartWork.Set(tempString);

		//get status
		getline(file, tempString, '\n');
		tempEmployee.AtVacationStatus = atoi(tempString.c_str());

		// get notes
		getline(file, tempString, '\n');
		vector<string> tempVector = Date::SplitString(tempString, '~');

		if (tempVector.size() != 1 || tempVector[0] != "")
		{
			tempEmployee.Notes = tempVector;
		}

		list.Add(tempEmployee);
	}

	file.close();
}

void Menu()
{
	enum { EXIT, ADD, REMOVE, FIND, CORRECT, SHOW_ALL, BIRTHDAYS, RETIRED};

	while (true)
	{
		cout << "-------------------------------------------------\n\n";
		cout << "You are in menu!\n";
		cout << "Choose:\n";
		cout << "1) Add employee info\n";
		cout << "2) Remove employee info\n";
		cout << "3) Find employee\n";
		cout << "4) Correct employee info\n";
		cout << "5) Show all employees info\n";
		cout << "6) Birthdays\n";
		cout << "7) List of people who could be retired (more than 60 years old)\n";
		cout << "0) Exit\n";

		cout << "Your option: ";

		int choise = GetOption(0, 7);

		switch (choise)
		{
		case ADD:
			AddEmployee();
			break;
		case REMOVE:
			RemoveEmployee();
			break;
		case FIND:
			MenuSearch();
			break;
		case CORRECT:
			CorrectEmployeeInfo();
			break;
		case SHOW_ALL:
			ShowAllEmployees();
			break;
		case BIRTHDAYS:
			ShowBirthdays();
			break;
		case RETIRED:
			DismissalOrder();
			break;
		case EXIT:
			return;
		}
	}
}

void MenuSearch()
{
	cout << "Search by:\n";
	cout << "1) Name\n";
	cout << "2) Date of birth (after day that you will input)\n";
	cout << "3) Passport number\n";
	cout << "4) Social security number\n";
	cout << "5) Education\n";
	cout << "6) Position\n";
	cout << "7) Salary (higher then you will input)\n";
	cout << "8) Date of work start (after day that you will input)\n";
	cout << "9) Work status\n";
	cout << "0) Back to main menu\n";

	int choise = GetOption(0, 9);

	if (choise != 0)
	{
		vector<int> founded = FindEmployees(choise);

		if (founded.size() == 0)
		{
			cout << "No matching results found!\n\n";
		}
		else if (founded.size() > 1)
		{
			cout << "Several employees were found:\n\n";

			for (size_t i = 0; i < founded.size(); i++)
			{
				cout << i + 1 << ")\n";
				ShowEmployeeInfo(list.GetAt(founded[i]));
			}
		}
		else
		{
			ShowEmployeeInfo(list.GetAt(0));
		}
	}
	
	cout << "Press any button to return to the menu.\n\n";
	_getch();
}

void AddEmployee()
{
	enum { NAME = 1, BIRTH, PASSPORT_NUM, SOCIAL_NUM, EDUCATION, POSITION, SALARY, WORK_START, STATUS };

	Employee tempEmployee;
	
	InputInfo(tempEmployee, NAME);
	InputInfo(tempEmployee, BIRTH);
	InputInfo(tempEmployee, PASSPORT_NUM);
	InputInfo(tempEmployee, SOCIAL_NUM);
	InputInfo(tempEmployee, EDUCATION);
	InputInfo(tempEmployee, POSITION);
	InputInfo(tempEmployee, SALARY);
	InputInfo(tempEmployee, WORK_START);
	InputInfo(tempEmployee, STATUS);

	tempEmployee.SetNotes();

	list.Add(tempEmployee);
}

void RemoveEmployee()
{
	string tempString;

	cout << "Enter the name of the employee whose information you want to delete: ";
	getline(cin, tempString);

	vector<int> founded = list.FindByName(tempString);

	if (founded.size() == 0)
	{
		cout << "No matching results found!\n\n";
	}
	else if (founded.size() > 1)
	{
		cout << "Several employees were found:\n\n";

		for (size_t i = 0; i < founded.size(); i++)
		{
			cout << i + 1 << ")\n";
			ShowEmployeeInfo(list.GetAt(i));
		}

		cout << "Which one you want to delete: ";

		int choise = GetOption(1, founded.size()) - 1;

		list.Remove(tempString, list.GetAt(choise).SocialSecurityNumber);
	}
	else
	{
		list.Remove(tempString);
	}
}

void ShowAllEmployees()
{
	int ListSize = list.GetSize();
	
	for (size_t i = 0; i < ListSize; i++)
	{
		Employee tempEmployee = list.GetAt(i);

		cout << i + 1 << ") \n";

		ShowEmployeeInfo(tempEmployee);
	}

	cout << "Press any button to return to the menu.\n\n";
	_getch();
}

void CorrectEmployeeInfo()
{
	vector<int> founded = FindEmployees(1);

	if (founded.size() == 0)
	{
		cout << "No matching results found!\n\n";
	}
	else 
	{
		int choiseEmployee;

		if (founded.size() > 1)
		{
			cout << "Several employees were found:\n\n";

			for (size_t i = 0; i < founded.size(); i++)
			{
				cout << i + 1 << ")\n";
				ShowEmployeeInfo(list.GetAt(i));
			}

			cout << "Choose one of them (input number): ";
		
			choiseEmployee = GetOption(1, founded.size()) - 1;
		}
		else
		{
			choiseEmployee = 0;
		}

		Employee tempEmployee = list.GetAt(founded[choiseEmployee]);
		list.Remove(tempEmployee.Name, tempEmployee.SocialSecurityNumber);

		int choiseField;

		cout << "What field would you like to choose?\n" <<
			"1 - name, 2 - date of birth, 3 - passport number, 4 - social number,\n" <<
		    "5 - education, 6 - position, 7 - salary, 8 - start work date, 9 - status\n" <<
			"Input: ";

		choiseField = GetOption(1, 9);

		InputInfo(tempEmployee, choiseField);

		list.Add(tempEmployee);
	}

	cout << "Press any button to return to the menu.\n\n";
	_getch();
}

void ShowBirthdays()
{
	Date today = Date::GetCurrentDate();

	vector<string> CurrentDate = Date::SplitString(today.GetAsString(), '/');

	int count = 0;

	cout << "List of people who have a birthday in the next 50 days:\n\n";

	for (size_t i = 0; i < list.GetSize(); i++)
	{
		Employee tempEmployee = list.GetAt(i);

		string BirthDate = tempEmployee.BirthDate.GetAsString();

		BirthDate.replace(6, 4, CurrentDate[2]);

		tempEmployee.BirthDate.Set(BirthDate);

		if (today - tempEmployee.BirthDate < 50)
		{			
			count++;
			
			cout << count << ": " + tempEmployee.Name + '\n' + tempEmployee.BirthDate.GetAsString() + "\n\n";
		}
	}

	if (count == 0)
	{
		cout << "No one has a birthday in the next 50 days.\n\n";
	}

	cout << "Press any button to return to the menu.\n\n";
	_getch();
}

void DismissalOrder()
{
	vector<Employee> MayBeRetired(0);
	string today = Date::GetCurrentDate().GetAsString();

	for (size_t i = 0; i < list.GetSize(); i++)
	{
		Employee tempEmployee = list.GetAt(i);

		string BirthDate = tempEmployee.BirthDate.GetAsString();
		vector<string> Date = Date::SplitString(BirthDate, '/');
		int BirthYear = atoi(Date[2].c_str());

		vector<string> CurrentDate = Date::SplitString(today, '/');
		int CurrentYear = atoi(CurrentDate[2].c_str());

		if ((CurrentYear - BirthYear) >= 60)
		{
			MayBeRetired.push_back(tempEmployee);
		}
	}

	if (MayBeRetired.size() > 0)
	{
		cout << "List of people who could be retired:\n\n";

		int RetiredSize = MayBeRetired.size();

		for (size_t i = 0; i < RetiredSize; i++)
		{
			cout << i + 1 << ")\n";
			ShowEmployeeInfo(MayBeRetired[i]);				
		}

		cout << "Choose who to retire (0 if no one)\n";

		int choise = GetOption(0, RetiredSize);

		if (choise > 0)
		{
			string tomorrow = Date::GetCurrentDate().GetAsString();

			Employee tempEmployee = MayBeRetired[choise - 1];

			fstream dismissalFile(dismissalOrderPath + tempEmployee.Name + ".txt", std::ios::out);

			dismissalFile << "DISMISSAL ORDER\n\n";
			dismissalFile << "Employee " << tempEmployee.Name <<
				" born at " << tempEmployee.BirthDate.GetAsString() <<
				" is retired from roday (" << today << ")\n" << 
				" because of reaching retirement age\n\n";
			dismissalFile << "Manager's signature: ";
		}
	}
	else
	{
		cout << "No people who could be retired.";
	}

	cout << "Press any button to return to the menu.\n\n";
	_getch();
}

void InputInfo(Employee & pEmployee, int pFieldChoise)
{
	enum { NAME = 1, BIRTH, PASSPORT_NUM, SOCIAL_NUM, EDUCATION, POSITION, SALARY, WORK_START, STATUS };

	string tempString;

	switch (pFieldChoise)
	{
	case NAME:
		pEmployee.SetName();
		break;
	case BIRTH:
		pEmployee.SetBirthDate();
		break;
	case PASSPORT_NUM:
		pEmployee.SetPassportNumber();
		break;
	case SOCIAL_NUM:
		pEmployee.SetSocialSecurityNumber();
		break;
	case EDUCATION:
		pEmployee.SetEducation();
		break;
	case POSITION:
		pEmployee.SetPosition();
		break;
	case SALARY:
		pEmployee.SetSalary();
		break;
	case WORK_START:
		pEmployee.SetStartWork();
		break;
	case STATUS:
		pEmployee.SetStatus();
		break;
	}
}

void WriteNewDataToFile()
{
	fstream file(filePath, std::ios::out);
	
	int ListSize = list.GetSize();

	for (size_t i = 0; i < ListSize; i++)
	{
		Employee tempEmployee = list.GetAt(i);

		file << tempEmployee.Name + "\n";
		file << tempEmployee.BirthDate.GetAsString() + "\n";
		file << tempEmployee.PassportNumber + "\n";
		file << tempEmployee.SocialSecurityNumber + "\n";
		file << tempEmployee.Education + "\n";
		file << tempEmployee.Position + "\n";
		file << tempEmployee.Salary << "\n";
		file << tempEmployee.StartWork.GetAsString() + '\n';
		file << tempEmployee.AtVacationStatus << '\n';

		if (tempEmployee.Notes.size() != 0)
		{
			size_t j;

			for (j = 0; j < tempEmployee.Notes.size() - 1; j++)
			{
				file << tempEmployee.Notes[j] + '~';
			}

			file << tempEmployee.Notes[j];
		}

		if (i != ListSize - 1)
		{
			file << '\n';
		}
	}

	file.close();
}

vector<int> FindEmployees(int pChoise)
{
	enum {NAME = 1, BIRTH, PASSPORT_NUM, SOCIAL_NUM, EDUCATION, POSITION, SALARY, WORK_START, STATUS};

	string tempString;
	vector<int> founded(0);

	switch (pChoise)
	{
	case NAME:
		founded = list.FindByName();
		break;
	case BIRTH:
		founded = list.FindByBirthDate();
		break;
	case PASSPORT_NUM:
		founded = list.FindByPassportNumber();
		break;
	case SOCIAL_NUM:
		founded = list.FindBySocialSecurityNumber();
		break;
	case EDUCATION:
		founded = list.FindByEducation();
		break;
	case POSITION:
		founded = list.FindByPosition();
		break;
	case SALARY:
		founded = list.FindBySalary();
		break;
	case WORK_START:
		founded = list.FindByStartWork();
		break;
	case STATUS:
		cout << "Choose status (1 - working, 2 - at vacation): ";
		getline(cin, tempString);
		founded = list.FindByAtVacationStatus();
	}

	return founded;
}

bool IsUnsignedDouble(string pString)
{
	if (pString.length() == 0)
	{
		return false;
	}

	for (size_t i = 0; i < pString.length(); i++)
	{
		if ((pString[i] < '0' || pString[i] > '9') && pString[i] != '.')
		{
			return false;
		}
	}

	return true;
}

bool IsUnsignedInt(string pString)
{
	if (pString.length() == 0)
	{
		return false;
	}

	for (size_t i = 0; i < pString.length(); i++)
	{
		if (pString[i] < '0' || pString[i] > '9')
		{
			return false;
		}
	}

	return true;
}

int GetOption(int pLow, int pHigh)
{
	int choise;

	while (true)
	{
		choise = static_cast<int>(_getch() - 48);

		cout << choise << '\n';

		if (choise <= pHigh && choise >= pLow)
		{
			return choise;
		}

		cout << "Wrong input, try again: ";
	}
}

void ShowEmployeeInfo(Employee pEmployee)
{
	cout << "Name: " + pEmployee.Name + '\n';
	cout << "Date of birth: " + pEmployee.BirthDate.GetAsString() + '\n';
	cout << "Passport number: " + pEmployee.PassportNumber + '\n';
	cout << "Social security number: " + pEmployee.SocialSecurityNumber + '\n';

	cout << "Education: ";
	if (pEmployee.Education == "")
	{
		cout << "None\n";
	}
	else
	{
		cout << pEmployee.Education + '\n';
	}

	cout << "Salary: " << pEmployee.Salary << '\n';
	cout << "Date of work start: " + pEmployee.StartWork.GetAsString() + '\n';
	cout << "Status: " << (pEmployee.AtVacationStatus ? "At vacation" : "At work") << '\n';

	Date today = Date::GetCurrentDate();
	int	WorkingDays = abs(today - pEmployee.StartWork);
	int VacationWeeks = (WorkingDays / 183) * 2;
	cout << "Has " << VacationWeeks << " vacation weeks\n";

	cout << "Notes:\n";

	if (pEmployee.Notes.size() == 0)
	{
		cout << "   " << "None.\n";
	}
	else
	{
		for (size_t i = 0; i < pEmployee.Notes.size(); i++)
		{
			cout << "   " << i + 1 << ": " + pEmployee.Notes[i] + '\n';
		}
	}

	cout << "\n\n";
}
