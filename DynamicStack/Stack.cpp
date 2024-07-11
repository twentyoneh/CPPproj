#include "Stack.h"

Stack::Stack() : 
	first{ nullptr }, last{nullptr} {}

Stack::Stack(int val)
{
	Node tmpNode(val);
	first = new Node;
	first = &tmpNode;
	last = &tmpNode;
}

Stack::~Stack()
{
	while (!isEmpty())
	{
		Node* tmp = last->next;
		
		if(tmp == first)
		{
			delete[] first;
			break;
		} 
		else if (tmp != nullptr) {
			delete[] last;
			last = tmp;
		}
	}
}

void Stack::Push(int val)
{
	Node* p = new Node(val);
	if (isEmpty()) {
		first = p;
		last = p;
		return;

	}
	p->next = last;
	last = p;
}

void Stack::Pop()
{
	Node* tmp = new Node();
	tmp = last->next;
	delete[] last;
	last = tmp;
	
}

Node Stack::Peek()
{
	return last;
}

bool Stack::isEmpty()
{
	return first == nullptr;
}
