#pragma once
#include "Node.h"

template <typename T>
class Stack {
private:
	Node<T>* top;
public:
	Stack();
	bool isEmpty();
	bool push(const T& newEntry);
	bool pop(T& TopEntry);
	bool peek(T& TopEntry);
	void ReverseMeToArray(Stack S);
	Node<T>* getTop();
	T* toArray(int& count);
	~Stack();
};

template <typename T>
Stack<T>::Stack() {
	top = nullptr;
}

template <typename T>
bool Stack<T>::isEmpty() {
	return (top == nullptr);
}

template <typename T>
bool Stack<T>::push(const T& newEntry) {
	Node<T>* nptr = new Node<T>;
	nptr->setItem(newEntry);
	nptr->setNext(top);
	top = nptr;
	return 1;
}

template <typename T>
bool Stack<T>::pop(T& TopEntry) {
	if (top == nullptr) {
		return 0;
	}
	else {
		TopEntry = top->getItem();
		Node<T>* ptr = top;
		top = ptr->getNext();
		delete ptr;
		return 1;
	}
}

template <typename T>
bool Stack<T>::peek(T& TopEntry) {
	if (top == nullptr) {
		return 0;
	}
	TopEntry = top->getItem();
	return 1;
}

template <typename T>
T* Stack<T>::toArray(int& count)
{
	count = 0;

	if (!top)
		return nullptr;
	//counting the no. of items in the Stack
	Node<T>* p = top;
	while (p)
	{
		count++;
		p = p->getNext();
	}

	T* Arr = new T[count];
	p = top;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

template <typename T>
Node<T>* Stack<T>::getTop()
{
	return top;
}

template <typename T>
void Stack<T>::ReverseMeToArray(Stack S)
{
	ArrayStack<T> Rev(S.getCapacity());	//First creat a stack 
	T Item;
	while (S.pop(Item))	//pop from S
	{
		Rev.push(Item); //push into Rev
	}
	count = 0;

	if (!top)
		return nullptr;
	//counting the no. of items in the Stack
	Node<T>* p = Rev;
	while (p)
	{
		count++;
		p = p->getNext();
	}

	T* Arr = new T[count];
	p = top;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

template <typename T>
Stack<T>::~Stack() {
	Node<T>* ptr = top;
	while (ptr != nullptr) {
		top = ptr->getNext();
		delete ptr;
		ptr = top;
	}
}