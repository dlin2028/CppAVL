#pragma once

template <typename T>
Tree<T>::Tree(T value, Node<T>* parent)
{
	Value = value;
}

template<typename T>
Tree<T>::~Tree()
{
	std::shared_ptr<Node<T>> temp = std::move(NextNode);
	while (temp)
	{
		temp = std::move(NextNode);
	}
}

template<typename T>
Tree<T>::rotateRight(Node<T>* middleNode)
{
	Node<T>* oldRightNode = middleNode->
}