#include "stdafx.h"
#include "TernaryTree.h"

void TernaryTree::SetMiddleBranch(std::string pString, int pBegin, Node* &pStartingPoint)
{
	pStartingPoint = new Node;

	Node* temp_node = pStartingPoint;

	for (size_t i = pBegin; i < pString.length(); i++)
	{
		temp_node->value = pString[i];
		SetNullptrChildren(temp_node);

		if (i != pString.length() - 1)
		{
			temp_node->middle = new Node;
			temp_node = temp_node->middle;
		}
	}
}

void TernaryTree::SetNullptrChildren(Node * pNode)
{
	pNode->left = pNode->right = pNode->middle = nullptr;
}

void TernaryTree::InsertNew(std::string pValue, int pStringAt, Node* &pCurrentNode)
{
	if (pStringAt == pValue.length())
	{
		return;
	}

	if (pCurrentNode == nullptr)
	{
		SetMiddleBranch(pValue, pStringAt, pCurrentNode);
		return;
	}
	else if (pCurrentNode->value == pValue[pStringAt])
	{
		if (pCurrentNode->middle->value == pValue[pStringAt + 1])
		{
			InsertNew(pValue, pStringAt + 1, pCurrentNode->middle);
		}
		else if (pCurrentNode->middle->value > pValue[pStringAt + 1])
		{
			InsertNew(pValue, pStringAt + 1, pCurrentNode->left);
		}
		else
		{
			InsertNew(pValue, pStringAt + 1, pCurrentNode->right);
		}
	}
	else if (pCurrentNode->middle->value > pValue[pStringAt])
	{
		InsertNew(pValue, pStringAt, pCurrentNode->left);
	}
	else
	{
		InsertNew(pValue, pStringAt, pCurrentNode->right);
	}
}

int TernaryTree::Depth(Node* pCurrentNode)
{
	if (pCurrentNode == nullptr)
	{
		return 0;
	}
	
	int leftDepth = Depth(pCurrentNode->left);
	int middleDepth = Depth(pCurrentNode->middle);
	int rightDepth = Depth(pCurrentNode->right);

	return std::fmax(leftDepth + 1, std::fmax(middleDepth + 1, rightDepth + 1));
}

void TernaryTree::DestroySubTree(Node * pCurrentNode)
{
	if (pCurrentNode != nullptr)
	{
		if (pCurrentNode->left != nullptr)
		{
			DestroySubTree(pCurrentNode->left);
		}

		if (pCurrentNode->middle != nullptr)
		{
			DestroySubTree(pCurrentNode->middle);
		}

		if (pCurrentNode->right != nullptr)
		{
			DestroySubTree(pCurrentNode->right);
		}

		delete pCurrentNode;
	}
}