#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "Node.h"

template<typename T>
class Tree
{
public:
	int Count;
	Tree();
	~Tree();

	bool Insert(T);
	void Delete(T);
	void InOrder();

private:
	int currentHeight;
	std::unique_ptr<Node<T>> head;
	void rotateLeft(Node<T>* middleNode);
	void rotateRight(Node<T>* middleNode);
	bool insert(T, Node<T>* top);
	bool InsertRec(T val);
	std::unique_ptr<Node<T>> RecursiveInsert(std::unique_ptr<Node<T>> root, T val);

	void balanceTree(Node<T>* currentNode);
	Node<T>* search(T key, Node<T>* currentNode);
	void inOrder(Node<T>* currentNode);
	std::string output;
};

template <typename T>
Tree<T>::Tree()
{
	head.reset();
}

template<typename T>
Tree<T>::~Tree()
{
	head.reset();
}

template<typename T>
void Tree<T>::rotateRight(Node<T>* middleNode)
{
	//dont die
	std::unique_ptr<Node<T>> oldRightNode = move(middleNode->RightNode);

	//middlenode.rightnode = middlenode.parent
	middleNode->RightNode = middleNode->parent->parent->MoveChild(middleNode->parent);

	//moved here so middlenode doesnt die
	if (!middleNode->parent->parent)
	{
		head = middleNode->parent->parent->MoveChild(middleNode);
	}

	//middlenode.parent = middlenode.rightnode.parent
	middleNode->parent = middleNode->RightNode->parent;

	//middleNode.RightNode.Parent = middleNode;
	middleNode->RightNode->parent = middleNode;

	//middleNode.RightNode.LeftNode = oldRightNode;
	middleNode->RightNode->LeftNode = move(oldRightNode);
}

template<typename T>
void Tree<T>::rotateLeft(Node<T>* middleNode)
{
	//dont die
	std::unique_ptr<Node<T>> oldLeftNode = move(middleNode->LeftNode);

	//middlenode.Leftnode = middlenode.parent
	middleNode->LeftNode = middleNode->parent->parent->MoveChild(middleNode->parent);

	//moved here so middlenode doesnt die
	if (!middleNode->parent->parent)
	{
		head = middleNode->parent->parent->MoveChild(middleNode);
	}

	//middlenode.parent = middlenode.Leftnode.parent
	middleNode->parent = middleNode->LeftNode->parent;

	//middleNode.LeftNode.Parent = middleNode;
	middleNode->LeftNode->parent = middleNode;

	//middleNode.LeftNode.RightNode = oldLeftNode;
	middleNode->LeftNode->RightNode = move(oldLeftNode);
}

template<typename T>
bool Tree<T>::Insert(T item)
{
	return insert(item, head.get());
}

template<typename T>
void Tree<T>::Delete(T key)
{
	Node<T>* foundNode = search(key, head.get());
	foundNode->parent->RemoveChild(foundNode);
	balanceTree(head.get());
}

template<typename T>
bool Tree<T>::insert(T item, Node<T>* currentNode)
{
	if (!currentNode)
	{
		if (!head)
		{
			head = std::make_unique<Node<T>>(item, nullptr); 	
			return false;
		}
		currentHeight = 1;
		return true;
	}
	if (item < currentNode->Item)
	{
		if (insert(item, currentNode->LeftNode.get()))
		{
			currentNode->LeftNode = std::make_unique<Node<T>>(item, nullptr);
			currentNode->LeftNode->parent = currentNode;
		}
	}
	else
	{
		if (insert(item, currentNode->RightNode.get()))
		{
			currentNode->RightNode = std::make_unique<Node<T>>(item, nullptr);
			currentNode->RightNode->parent = currentNode;
		}
	}
	currentNode->Height = ++currentHeight;

	//rebalance tree
	if (currentNode->GetBalance() > 1)
	{
		rotateLeft(currentNode->RightNode.get());
	}
	else if (currentNode->GetBalance() < -1)
	{
		rotateRight(currentNode->LeftNode.get());
	}
	return false;
}

template<typename T>
 bool Tree<T>::InsertRec(T val)
{
	 if (!head)
	 {
		 Count++;
		 head = std::make_unique<Node<T>>(val);
		 return true;
	}
	 else
	 {
		 head = RecursiveInsert(std::move(head), val);
	 }
}


template<typename T>
void Tree<T>::InOrder()
{
	 inOrder(head.get());
}

template<typename T>
void Tree<T>::balanceTree(Node<T>* currentNode)
{
	if (!currentNode)
	{
		return;
	}

	balanceTree(currentNode->LeftNode.get());
	balanceTree(currentNode->RightNode.get());

	currentNode->Height = ++currentHeight;
	if (currentNode->GetBalance() > 1)
	{
		rotateLeft(currentNode->RightNode.get());
	}
	else if (currentNode->GetBalance() < -1)
	{
		rotateRight(currentNode->LeftNode.get());
	}
}

template<typename T>
Node<T>* Tree<T>::search(T key, Node<T>* currentNode)
{
	if (!currentNode)
	{
		return nullptr;
	}

	if (currentNode->Item > key)
	{
		return search(key, currentNode->LeftNode.get());
	}
	else if (currentNode->Item != key)
	{
		return search(key, currentNode->RightNode.get());
	}
	else
	{
		return currentNode;
	}
}

template<typename T>
void Tree<T>::inOrder(Node<T>* currentNode)
{
	
	if (currentNode == nullptr)
	{
		return;
	}
	inOrder(currentNode->LeftNode.get());
	std::cout << currentNode->Item;
	inOrder(currentNode->RightNode.get());
}