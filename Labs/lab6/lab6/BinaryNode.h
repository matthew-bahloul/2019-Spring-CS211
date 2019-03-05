#pragma once

template <typename T>
class BinaryNode
{
private:
	T _value;
	BinaryNode* _left_child = nullptr;
	BinaryNode* _right_child = nullptr;

public:
	BinaryNode(const T& value)
	{
		_value = value;
	}

	// getters
	T& getValue()
	{
		return _value;
	}
	const T& getValue() const
	{
		return _value;
	}
	BinaryNode* getLeft()
	{
		return _left_child;
	}
	BinaryNode* getRight()
	{
		return _right_child;
	}

	// setters
	void setValue(const T& value)
	{
		_value = value;
	}
	void setLeft(BinaryNode* left)
	{
		_left_child = left;
	}
	void setRight(BinaryNode* right)
	{
		_right_child = right;
	}

};