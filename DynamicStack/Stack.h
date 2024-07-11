#pragma once
#include"Node.cpp"
class Stack
{
public:
	Stack();
	Stack(int);
	~Stack();

	void Push(int);
	void Pop();
	Node Peek();
	bool isEmpty();

private:
	Node* first;
	Node* last;
};

