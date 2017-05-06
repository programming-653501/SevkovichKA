#pragma once
#include "Employee.h"
#include <vector>
#include <iostream>
#include <string>

class ListEmployees
{
protected:
	struct Node
	{
		Employee value;
		Node* next;
		Node* prev;

		Node() {  }
	};

	void deleteNode(Node* &pNode);

	Node* head;
	unsigned size;

public:
	ListEmployees()
	{
		head = nullptr;
		size = 0;
	}

	~ListEmployees();

	void Add(Employee pNewEmployee);
	void Remove(std::string pName, std::string pSocialSecurityNumber = "");

	std::vector<int> FindByName(std::string pName = "");
	std::vector<int> FindByBirthDate();
	std::vector<int> FindByPassportNumber();
	std::vector<int> FindBySocialSecurityNumber();
	std::vector<int> FindByEducation();
	std::vector<int> FindByPosition();
	std::vector<int> FindBySalary();
	std::vector<int> FindByStartWork();
	std::vector<int> FindByStatus();
	std::vector<int> FindByAtVacationStatus();

	Employee GetAt(int index);//todo
	int GetSize();
	bool IsEmpty();
};
