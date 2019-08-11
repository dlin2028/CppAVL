#pragma once

template <typename T>
Node<T>::Node(T value, Node<T>* parent)
{
	Value = value;
}

template<typename T>
Node<T>::~Node()
{
	std::shared_ptr<Node<T>> temp = std::move(NextNode);
	while (temp)
	{
		temp = std::move(NextNode);
	}
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
void Node<T>::SetChild(std::unique_ptr<Node<T>> child)
{
	if (child->parent == LeftNode.get())
	{
		LeftNode = std::move(child);
	}
	RightNode = std::move(child);
}