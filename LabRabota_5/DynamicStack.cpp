#include "stdafx.h"
#include "DynamicStack.h"

DynamicStack::~DynamicStack()
{
	StackNode *nodePtr = nullptr;
	StackNode *nextNode = nullptr;

	nodePtr = top;

	while (nodePtr != nullptr)
	{
		nextNode = nodePtr->Next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

void DynamicStack::push(double value)
{
	StackNode *newNode = new StackNode;

	newNode->value = value;

	if (isEmpty())
	{
		top = newNode;
		newNode->Next = nullptr;
	}
	else
	{
		newNode->Next = top;
		top = newNode;
	}
}

double DynamicStack::pop()
{
	if (isEmpty())
	{
		std::string Empty = "Stack is empty!\n";
		throw Empty;
	}

	double t = top->value;

	StackNode* temp = top->Next;

	delete top;

	top = temp;

	return t;
}

bool DynamicStack::isEmpty()
{
	if (top == nullptr)
	{
		return true;
	}

	return false;
}

void DynamicStack::Reverse()
{
	if (isEmpty())
	{
		std::string Empty = "Stack is empty!\n";
		throw Empty;
	}

	DynamicStack* Stack_temp = new DynamicStack;

	while(this->isEmpty() == false)
	{
		Stack_temp->push(this->pop());
	}
	
	std::swap(this->top, Stack_temp->top);

	delete Stack_temp;
}