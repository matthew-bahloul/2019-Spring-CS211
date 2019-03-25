#pragma once
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "BinaryNode.h"

using namespace std;

template <typename T>
class BinarySearchTree
{
protected:
	BinaryNode<T>* _root = nullptr;

	virtual BinaryNode<T>* bstAdd(BinaryNode<T>* node, int value)
	{
		//null node indicates time to create a new item in our tree
		if (node == nullptr)
		{
			node = new BinaryNode<T>{ value };
			return node;
		}

		//if not null, send result to child based on relation of node's value
		//and new value
		if (value >= node->getValue())
		{
			node->setRight(bstAdd(node->getRight(), value));
		}
		else
		{
			node->setLeft(bstAdd(node->getLeft(), value));
		}

		//to maintian recursive correctness, always return a BinaryNode<T>*
		return node;
	}

	virtual BinaryNode<T>* bstRemove(BinaryNode<T>* node, int value)
	{
		//ALWAYS guard against a null ptr
		if (node == nullptr)
		{
			return nullptr;
		}

		if (node->getValue() == value)
		{
			//case #1: no children
			if (node->getLeft() == nullptr && node->getRight() == nullptr)
			{
				delete node;
				return nullptr;
			}
			else if (node->getLeft() == nullptr || node->getRight() == nullptr)
			{
				//a little verbose, but completely okay. Not any slower than
				//other method.
				/*BinaryNode<T>* child = node->getLeft();
				if (child == nullptr)
				{
				   child = node->getRight();
				}*/
				//same thing as above
				BinaryNode<T>* child = node->getLeft() == nullptr
					? node->getRight()
					: node->getLeft();
				delete node;
				return child;
			}
			else
			{
				//two children.  Grab rightmost in left subtree
				BinaryNode<T>* largest = node->getLeft();
				while (largest->getRight() != nullptr)
				{
					largest = largest->getRight();
				}

				//take largest's value
				node->setValue(largest->getValue());
				largest = bstRemove(node->getLeft(), largest->getValue());

				//reassign left side to be reconfiguration resulting from
				//delete
				node->setLeft(largest);
			}
		}
		else if (value > node->getValue())
		{
			BinaryNode<T>* result = bstRemove(node->getRight(), value);
			node->setRight(result);
		}
		else
		{
			BinaryNode<T>* result = bstRemove(node->getLeft(), value);
			node->setLeft(result);
		}
		return node;
	}

	BinaryNode<T>* getRoot() const
	{
		return _root;
	}

public:
	virtual void addElement(const T& value)
	{
		_root = bstAdd(_root, value);
	}

	virtual void removeElement(const T& value)
	{
		_root = bstRemove(_root, value);
	}


	int height(BinaryNode<T>* start) const
	{
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

	int size(BinaryNode<T>* start)
	{
		if (start == nullptr)
		{
			return 0;
		}

		return 1 + size(start->getLeft()) + size(start->getRight());
	}

	bool isAvlHelper(BinaryNode<T>* node) const
	{
		if (node == nullptr)
		{
			return true;
		}

		int left_branch_height = height(node->getLeft());
		int right_branch_height = height(node->getRight());

		if ((left_branch_height - right_branch_height < 2 && left_branch_height - right_branch_height > -2)
			&& isAvlHelper(node->getLeft())
			&& isAvlHelper(node->getRight()))
		{
			return true;
		}
		return false;
	}

	/*
	This function returns true when the supplied binary search tree is AVL compliant
	(difference between left and right height is no more than 1). True at all levels of the tree.
	*/
	bool isAvl() const
	{
		//LAB 7 TODO: Implement!
		return isAvlHelper(_root);
	}

	/*
	Merges the supplied BST into the current BST in such a way that the BST property is maintained
	*/
	void mergeTree(const BinarySearchTree<T>& other)
	{
		//LAB 7 TODO: Implement!
		mergeTreeHelper(other.getRoot());
	}

	void mergeTreeHelper(BinaryNode<T>* node)
	{
		if (node == nullptr)
		{
			return;
		}
		mergeTreeHelper(node->getLeft());
		mergeTreeHelper(node->getRight());

		addElement(node->getValue());
	}

	/*
	For this function, determine the closest common ancestor of both values in the tree.  If one value is not in the tree, output "NONE".  For example, given the tree:
			 10
		 5       15
	  1    6   11   17

	  * Values 1 and 5 share the ancestor 5 (parent-child relationship).
	  * Values 1 and 6 share the ancestor 5 (sibling relationship).
	  * Values 6 and 11 share the ancestor 10 (grandparent relationship).
	  Return -1 if there is no common ancestor.
	*/
	int commonAncestor(int val1, int val2)
	{
		if (commonAncestorHelper(_root, val1, val2) == nullptr)
		{
			return -1;
		}

		return commonAncestorHelper(_root, val1, val2)->getValue();

	}

	BinaryNode<T>* commonAncestorHelper(BinaryNode<T>* node, int val1, int val2)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		else if (val1 < node->getValue() && val2 < node->getValue())
		{
			return commonAncestorHelper(node->getLeft(), val1, val2);
		}
		else if (val1 > node->getValue() && val2 > node->getValue())
		{
			return commonAncestorHelper(node->getRight(), val1, val2);
		}

		return node;
	}

};

#endif // !BINARY_SEARCH_TREE_H