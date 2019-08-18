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
void Node<T>::GetChild(Node<T>* child)
{
	if(LeftNode)
}