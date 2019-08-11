#pragma once

template<typename T>
class Tree
{
public:
	int Count;
	Tree();
	~Tree();

	Insert(T);
	Delete(T);

private:
	unique_ptr<Node<T>> head;
	rotateLeft();
	rotateRight();
	insert();
};

