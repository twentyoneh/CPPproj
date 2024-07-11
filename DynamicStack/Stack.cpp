#include "Stack.h"

Stack::Stack() : 
	first{ nullptr }, last{nullptr} {}

Stack::Stack(int val) :
	first{&Node(val,nullptr)}
{

}

Stack::~Stack()
{
}

void Stack::Push(int val)
{
	Node* p = new Node(val);
	if (isEmpty()) {
		first = p;
		last = p;
		return;
	}
	last->next = p;
	last = p;
}

void Stack::Pop()
{
}

void Stack::Peek()
{
}

bool Stack::isEmpty()
{
	return first == nullptr;
}
