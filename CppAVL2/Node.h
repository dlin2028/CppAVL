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
	T Value;
	Node<T>* parent;
	void SetChild(std::unique_ptr<Node<T>> child);
	void RemoveChild(std::unique_ptr <Node<T>> child);
	int GetBalance();
};

#include "Node.tpp"