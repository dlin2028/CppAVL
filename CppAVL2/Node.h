#pragma once
#include <memory>

template <typename T>
class Node
{
public:
	~Node();
	Node(T, Node<T>* parent);
	std::unique_ptr<Node<T>> LeftNode;
	std::unique_ptr<Node<T>> RightNode;
	T Item;
	Node<T>* parent;
	void SetChild(std::unique_ptr<Node<T>> child);
	void RemoveChild(Node<T>* child);
	std::unique_ptr<Node<T>> MoveChild(Node<T>* child);

	int Height;
	int GetBalance();
};

#pragma once

template <typename T>
Node<T>::Node(T value, Node<T>* parent)
{
	Item = value;
}

template<typename T>
Node<T>::~Node()
{
	LeftNode.reset();
	RightNode.reset();
}

template<typename T>
int Node<T>::GetBalance()
{
	int bal = 0;
	if (LeftNode)
	{
		bal -= LeftNode->GetBalance();
	}
	if (RightNode)
	{
		bal += RightNode->GetBalance();
	}
	return bal;
}

template<typename T>
void Node<T>::RemoveChild(Node<T>* child)
{
	if (LeftNode.get() == child)
	{
		return LeftNode.reset();
	}
	else
	{
		return RightNode.reset();
	}
}

template<typename T>
std::unique_ptr<Node<T>> Node<T>::MoveChild(Node<T>* child)
{
	if (LeftNode.get() == child)
	{
		return std::move(LeftNode);
	}
	else
	{
		return std::move(RightNode);
	}
}