#pragma once
#include <string>
#include <string.h>
#include <locale>

class TernaryTree
{
private:
	struct Node
	{
		char value;
		Node* left;
		Node* middle;
		Node* right;
	};

	Node* root;

	void setMiddleBranch(std::string pString, int pBegin, Node* &pStartingPoint);
	void insert(std::string pValue, int pStringAt, Node* &pCurrentNode);
	void setNullptrChildren(Node* pNode);
	void destroySubtree(Node* pCurrentNode);
	int depth(Node* pCurrentNode);
	std::string toLower(std::string pValue);

public:
	TernaryTree()
	{
		root = nullptr;
	}

	void Add(std::string pValue)
	{
		pValue = toLower(pValue);

		if (root == nullptr)
		{
			setMiddleBranch(pValue, 0, root);
		}
		else
		{
			insert(pValue, 0, root);
		}
	}

	int GetDepth()
	{
		return depth(root);
	}

	~TernaryTree()
	{
		destroySubtree(root);
	}
};
