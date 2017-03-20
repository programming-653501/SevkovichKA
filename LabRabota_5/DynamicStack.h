#pragma once
#include "stdafx.h"
#include <string>

class DynamicStack
{
private:
	struct StackNode
	{
		double value;
		StackNode* Next;
	};

	StackNode* top;

public:
	DynamicStack()
	{
		top = nullptr;
	}

	~DynamicStack();

	void push(double);
	double pop();
	bool isEmpty();
	void Reverse();
};
