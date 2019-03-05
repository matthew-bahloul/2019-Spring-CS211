#include <iostream>
#include <string>

#include "BinaryNode.h"

using namespace std;

bool find(BinaryNode<int>* start, const int& to_find);
int size(BinaryNode<int>* start);
int height(BinaryNode<int>* start);
bool isFull(BinaryNode<int>* start);
void bstAdd(BinaryNode<int>* start, int value);


int main(void)
{
	BinaryNode<int>* root = new BinaryNode<int>{ 5 };
	root->setLeft(new BinaryNode<int>{ 12 });
	root->setRight(new BinaryNode<int>{ 4 });

	root->getLeft()->setLeft(new BinaryNode<int>{ 11 });
	root->getLeft()->setRight(new BinaryNode<int>{ 18 });

	root->getRight()->setLeft(new BinaryNode<int>{ 10 });
	root->getRight()->setRight(new BinaryNode<int>{ 7});

	root->getRight()->getLeft()->setLeft(new BinaryNode<int>{ 3 });
	root->getRight()->getLeft()->setRight(new BinaryNode<int>{ 9 });

	root->getRight()->getRight()->setRight(new BinaryNode<int>{ 15 });

	root->getRight()->getRight()->getRight()->setLeft(new BinaryNode<int>{ 20 });
	root->getRight()->getRight()->getRight()->setRight(new BinaryNode<int>{ 22 });

	cout << height(root);


	return 0;
}

bool find(BinaryNode<int>* start, const int& to_find)
{
	BinaryNode<int>* current_node = start;
	// check that the starting node exists
	if (start == nullptr)
	{
		return false;
	}

	// check that the starting point is the target value
	if (current_node->getValue() == start->getValue())
	{
		return true;
	}

	// recursive case: use the children as the starting point
	return find(start->getLeft(), to_find)
		|| find(start->getRight(), to_find);
}

int size(BinaryNode<int>* start)
{
	if (start == nullptr)
	{
		return 0;
	}

	return 1 + size(start->getLeft()) + size(start->getRight());
}

int height(BinaryNode<int>* start)
{
	int max = 0;

	if (start == nullptr)
	{
		return -1;
	}

	int left_height = height(start->getLeft());
	int right_height = height(start->getRight());

	int height = right_height;

	if (left_height > right_height)
	{
		height = left_height;
	}

	return 1 + height;
}

bool isFull(BinaryNode<int>* start)
{
	if (start == nullptr)
	{
		return true;
	}

	if (start->getLeft() != nullptr || start->getRight() == nullptr)
	{
		return false;
	}
	else if (start->getLeft() == nullptr || start->getRight() != nullptr)
	{
		return false;
	}

	return isFull(start->getLeft()) && isFull(start->getRight());
}

BinaryNode<int>* bstAdd(BinaryNode<int>* node, int value)
{
	if (node == nullptr)
	{
		node = new BinaryNode<int>{ value };
		return node;
	}
	if (value >= node->getValue())
	{
		node->setRight(bstAdd(node->getRight(), value));
	}
	else
	{
		node->setLeft(bstAdd(node->getLeft(), value));
	}
	return node;
}