#pragma once

class Node
{
public:
	int val;
	Node* next;

	Node(int int_val,Node* next) :
		val{int_val}, next{nullptr} {}
	Node(int val) : Node(val, nullptr) {}
	Node(Node* next) : Node(0, next) {}
	Node() : Node(0, nullptr) {}

	Node(Node&& other) noexcept : val{ other.val }, next{ other.next } {
		other.next = nullptr;
	}
	Node& operator=(Node&& other) noexcept {
		if (this != &other) {
			val = other.val;
			next = other.next;
			other.next = nullptr;
		}
		return *this;
	}
};