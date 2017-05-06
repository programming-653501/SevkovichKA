#include "stdafx.h"
#include "ListEmployees.h"

ListEmployees::~ListEmployees()
{
	while(!IsEmpty())
	{
		this->Remove(head->value.Name, head->value.SocialSecurityNumber);
	}
}

void ListEmployees::Remove(std::string pName, std::string pSocialSecurityNumber)
{
	Node* current_node = head;

	while (true)
	{
		if (current_node->value.Name == pName)
		{
			if (current_node->value.SocialSecurityNumber == pSocialSecurityNumber || pSocialSecurityNumber == "")
			{
				deleteNode(current_node);
				return;
			}
		}

		current_node = current_node->next;
	}
}

void ListEmployees::deleteNode(Node* &pNode)
{
	bool prevIsNULL = (pNode->prev == nullptr);
	bool nextIsNULL = (pNode->next == nullptr);

	if (prevIsNULL && !nextIsNULL)
	{
		pNode->next->prev = nullptr;
		head = head->next;
	}
	else if (!prevIsNULL && nextIsNULL)
	{
		pNode->prev->next = nullptr;
	}
	else if (!prevIsNULL && !nextIsNULL)
	{
		pNode->next->prev = pNode->prev;
		pNode->prev->next = pNode->next;
	}
	else
	{
		head = nullptr;
	}

	delete pNode;

	size--;
}

void ListEmployees::Add(Employee pNewEmployee)
{
	Node* temp_node = new Node;

	temp_node->value = pNewEmployee;

	if (this->IsEmpty())
	{
		head = temp_node;
		head->next = head->prev = nullptr;
	}
	else
	{
		temp_node->next = head;
		head->prev = temp_node;
		head = head->prev;
		head->prev = nullptr;
	}

	size++;
}

std::vector<int> ListEmployees::FindByName(std::string pName)
{
	std::vector<int> foundEmployees(0);
	Employee tempEmployee;

	if (pName == "")
	{
		tempEmployee.SetName();
	}
	else
	{
		tempEmployee.Name = pName;
	}

	for (size_t i = 0; i < this->size; i++)
	{
		Employee temp = GetAt(i);

		if (temp.Name == tempEmployee.Name)
		{
			foundEmployees.push_back(i);
		}
	}

	return foundEmployees;
}

std::vector<int> ListEmployees::FindByBirthDate()
{
	std::vector<int> foundEmployees(0);

	Employee tempEmployee;

	tempEmployee.SetBirthDate();

	for (size_t i = 0; i < this->size; i++)
	{
		Employee temp = GetAt(i);

		if (temp.BirthDate - tempEmployee.BirthDate < 0)
		{
			foundEmployees.push_back(i);
		}
	}

	return foundEmployees;
}

std::vector<int> ListEmployees::FindByPassportNumber()
{
	std::vector<int> foundEmployees(0);

	Employee tempEmployee;

	tempEmployee.SetPassportNumber();

	for (size_t i = 0; i < this->size; i++)
	{
		Employee temp = GetAt(i);

		if (temp.PassportNumber == tempEmployee.PassportNumber)
		{
			foundEmployees.push_back(i);
		}
	}

	return foundEmployees;
}

std::vector<int> ListEmployees::FindBySocialSecurityNumber()
{
	std::vector<int> foundEmployees(0);
	
	Employee tempEmployee;

	tempEmployee.SetSocialSecurityNumber();

	for (size_t i = 0; i < this->size; i++)
	{
		Employee temp = GetAt(i);

		if (temp.SocialSecurityNumber == tempEmployee.SocialSecurityNumber)
		{
			foundEmployees.push_back(i);
		}
	}

	return foundEmployees;
}

std::vector<int> ListEmployees::FindByEducation()
{
	std::vector<int> foundEmployees(0);

	Employee tempEmployee;

	tempEmployee.SetEducation();

	for (size_t i = 0; i < this->size; i++)
	{
		Employee temp = GetAt(i);

		if (temp.Education == tempEmployee.Education)
		{
			foundEmployees.push_back(i);
		}
	}

	return foundEmployees;
}

std::vector<int> ListEmployees::FindByPosition()
{
	std::vector<int> foundEmployees(0);

	Employee tempEmployee;

	tempEmployee.SetPosition();

	for (size_t i = 0; i < this->size; i++)
	{
		Employee temp = GetAt(i);

		if (temp.Position == tempEmployee.Position)
		{
			foundEmployees.push_back(i);
		}
	}

	return foundEmployees;
}

std::vector<int> ListEmployees::FindBySalary()
{
	std::vector<int> foundEmployees(0);

	Employee tempEmployee;

	tempEmployee.SetSalary();

	for (size_t i = 0; i < this->size; i++)
	{
		Employee temp = GetAt(i);

		if (temp.Salary >= tempEmployee.Salary)
		{
			foundEmployees.push_back(i);
		}
	}

	return foundEmployees;
}

std::vector<int> ListEmployees::FindByStartWork()
{
	std::vector<int> foundEmployees(0);

	Employee tempEmployee;

	tempEmployee.SetStartWork();

	for (size_t i = 0; i < this->size; i++)
	{
		Employee temp = GetAt(i);

		if ((temp.StartWork - tempEmployee.StartWork) < 0)
		{
			foundEmployees.push_back(i);
		}
	}

	return foundEmployees;
}

std::vector<int> ListEmployees::FindByStatus()
{
	std::vector<int> founded(0);

	Employee tempEmployee;

	tempEmployee.SetStatus();

	for (size_t i = 0; i < this->size; i++)
	{
		Employee temp = this->GetAt(i);
		if (temp.AtVacationStatus == tempEmployee.AtVacationStatus)
		{
			founded.push_back(i);
		}
	}

	return founded;
}

std::vector<int> ListEmployees::FindByAtVacationStatus()
{
	std::vector<int> foundEmployees(0);

	Employee tempEmployee;

	tempEmployee.SetPassportNumber();

	for (size_t i = 0; i < this->size; i++)
	{
		Employee temp = this->GetAt(i);
		if (temp.AtVacationStatus == tempEmployee.AtVacationStatus)
		{
			foundEmployees.push_back(i);
		}
	}

	return foundEmployees;
}

Employee ListEmployees::GetAt(int index)
{
	if (index > size)
	{
		std::string OutOfRange = "Out of range!";
		throw OutOfRange;
	}

	Node* temp = head;

	while (index > 0)
	{
		temp = temp->next;
		index--;
	}

	return temp->value;
}

int ListEmployees::GetSize()
{
	return this->size;
}

bool ListEmployees::IsEmpty()
{
	return (this->size == 0);
}
