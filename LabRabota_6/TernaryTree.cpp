#include "stdafx.h"
#include "TernaryTree.h"

void TernaryTree::setMiddleBranch(std::string pString, int pBegin, Node* &pStartingPoint)
{
	pStartingPoint = new Node;

	Node* temp_node = pStartingPoint;

	for (size_t i = pBegin; i < pString.length(); i++)
	{
		temp_node->value = pString[i];
		setNullptrChildren(temp_node);

		if (i != pString.length() - 1)
		{
			temp_node->middle = new Node;
			temp_node = temp_node->middle;
		}
	}
}

void TernaryTree::setNullptrChildren(Node * pNode)
{
	pNode->left = pNode->right = pNode->middle = nullptr;
}

void TernaryTree::insert(std::string pValue, int pCurrentPositionAtString, Node* &pCurrentNode)
{
	if (pCurrentPositionAtString == pValue.length())
	{
		return;
	}

	if (pCurrentNode == nullptr)
	{
		setMiddleBranch(pValue, pCurrentPositionAtString, pCurrentNode);
		return;
	}
	
	if (pCurrentNode->value == pValue[pCurrentPositionAtString])
	{
		insert(pValue, pCurrentPositionAtString + 1, pCurrentNode->middle);
	}
	else if (pCurrentNode->value > pValue[pCurrentPositionAtString])
	{
		insert(pValue, pCurrentPositionAtString, pCurrentNode->left);
	}
	else
	{
		insert(pValue, pCurrentPositionAtString, pCurrentNode->right);
	}
}

int TernaryTree::depth(Node* pCurrentNode)
{
	if (pCurrentNode == nullptr)
	{
		return 0;
	}

	int leftDepth = depth(pCurrentNode->left);
	int middleDepth = depth(pCurrentNode->middle);
	int rightDepth = depth(pCurrentNode->right);

	return std::fmax(leftDepth + 1, std::fmax(middleDepth + 1, rightDepth + 1));
}

std::string TernaryTree::toLower(std::string pValue)
{
	int StringSize = pValue.size();

	for (int i = 0; i < StringSize; i++)
	{
		if (pValue[i] >= 'A' && pValue[i] <= 'Z')
		{
			pValue[i] -= ('Z' - 'z');
		}
	}

	return pValue;
}

void TernaryTree::destroySubtree(Node * pCurrentNode)
{
	if (pCurrentNode != nullptr)
	{
		if (pCurrentNode->left != nullptr)
		{
			destroySubtree(pCurrentNode->left);
		}

		if (pCurrentNode->middle != nullptr)
		{
			destroySubtree(pCurrentNode->middle);
		}

		if (pCurrentNode->right != nullptr)
		{
			destroySubtree(pCurrentNode->right);
		}

		delete pCurrentNode;
	}
}
