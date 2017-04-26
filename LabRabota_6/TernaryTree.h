#pragma once
#include <string>

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

	void SetMiddleBranch(std::string pString, int pBegin, Node* &pStartingPoint);
	void InsertNew(std::string pValue, int pStringAt, Node* &pCurrentNode);
	void SetNullptrChildren(Node* pNode);
	void DestroySubTree(Node* pCurrentNode);
	int Depth(Node* pCurrentNode);

public:
	TernaryTree()
	{
		root = nullptr;
	}

	void Put(std::string pValue)
	{
		if (root == nullptr)
		{
			SetMiddleBranch(pValue, 0, root);
		}
		else
		{
			InsertNew(pValue, 0, root);
		}
	}

	int GetDepth()
	{
		return Depth(root);
	}

	~TernaryTree()
	{
		DestroySubTree(root);
	}
};

