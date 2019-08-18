#pragma once
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
	std::string InOrder();

private:
	int currentHeight;
	std::unique_ptr<Node<T>> head;
	void rotateLeft(Node<T>* middleNode);
	void rotateRight(Node<T>* middleNode);
	bool insert(T, Node<T>* top);
	void balanceTree(Node<T> currentNode);
	void search(T key, Node<T> currentNode);
	std::string inOrder();
	std::string output;
};

template <typename T>
Tree<T>::Tree()
{
	head = nullptr;
}

template<typename T>
Tree<T>::~Tree()
{
	head = nullptr;
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
	insert(item, head.get());
}

template<typename T>
bool Tree<T>::insert(T item, Node<T>* currentNode)
{
	if (!currentNode)
	{
		if (!head)
		{
			head = std::make_unique<Node<T>>(new Node<T>(item, nullptr)); 	
			return false;
		}
		currentHeight = 1;
		return true;
	}
	if (item < currentNode->Item)
	{
		if (insert(item, currentNode->LeftNode.get()))
		{
			currentNode->LeftNode = std::make_unique<Node<T>>(new Node<T>(item, nullptr));
			currentNode->LeftNode->parent = currentNode;
		}
	}
	else
	{
		if (insert(item, currentNode->RightNode.get()))
		{
			currentNode->RightNode = std::make_unique<Node<T>>(new Node<T>(item, nullptr));
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

std::string Tree<T> inOrder(TreeNode<T> currentNode)
{
	
	if (currentNode == null)
	{
		return;
	}
	inOrder(currentNode.LeftNode);
	
	inOrder(currentNode.RightNode);
}