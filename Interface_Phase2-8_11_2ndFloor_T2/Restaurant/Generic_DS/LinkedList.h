#pragma once

#include "Node.h"
#include "..\Rest\Order.h"
#include "..\Defs.h"

template<typename T>
class LinkedList {
private:
	Node<T>* Head;
public:
	LinkedList();
	bool isEmpty();
	void InsertBeg(const T& data);
	void InsertEnd(const T& data);
	bool DeleteNode(const T& value);
	bool DeleteNodes(const T& value);
	void DeleteFirst();
	void DeleteLast();
	bool Find(const T& value);
	void DeleteAll();
	bool removeOrder(T &pO);
	T* toArray(int& count);
	Order* returnOrder(ORD_TYPE);
	void deleteOrder(int oID, Order* pO);
	~LinkedList();
};



template<typename T>
LinkedList<T>::LinkedList() {
	Head = nullptr;
}

template<typename T>
void LinkedList<T>::InsertBeg(const T& data) {
	Node<T>* p = new Node<T>(data);
	p->setNext(Head);
	Head = p;
	return;
}

template<typename T>
void LinkedList<T>::InsertEnd(const T& data) {
	Node<T>* p = Head;
	Node<T>* np = new Node<T>(data);
	if (Head == nullptr) {
		Head = np;
		Head->setNext(nullptr);
		return;
	}
	while (p->getNext()) {
		p = p->getNext();
	}
	p->setNext(np);
	np->setNext(nullptr);
	return;
}

template<typename T>
bool LinkedList<T>::DeleteNode(const T& value) {
	Node<T>* p = Head;
	Node<T>* np = new Node<T>;
	if (Head == nullptr) {
		return false;
	}
	if (p->getItem() == value) {
		DeleteFirst();
		return true;
	}
	while (p->getNext()) {
		if (p->getNext()->getItem() == value) {
			np = p->getNext();
			p->setNext(np->getNext());
			delete np;
			return true;
		}
		else
			p = p->getNext();
	}
	if (p->getItem() == value) {
		DeleteLast();
		return true;
	}
	else
		return false;
}

template<typename T>
bool LinkedList<T>::DeleteNodes(const T& value) {
	Node<T>* p = Head;
	bool z;
	bool c = false;
	z = DeleteNode(p->getItem());
	while (z == 1) {
		c = true;
		if (p->getNext() != nullptr)
			p = p->getNext();
		else
			break;
		z = DeleteNode(p->getItem());
	}
	return c;
}

template<typename T>
void LinkedList<T>::DeleteFirst() {
	Node<T>* p = Head;
	if (Head == nullptr)
		return;
	else {
		Head = p->getNext();
		delete p;
	}
}

template<typename T>
void LinkedList<T>::DeleteLast() {
	Node<T>* p = Head;
	if (Head == nullptr)
		return;
	if (p->getNext() == nullptr) {
		DeleteFirst();
		return;
	}
	while (p->getNext()->getNext()) {
		p = p->getNext();
	}
	delete p->getNext();
	p->setNext(nullptr);
	return;
}

template<typename T>
bool LinkedList<T>::Find(const T& value) {
	Node<T>* p = Head;
	if (Head == nullptr) {
		return false;
	}
	while (p->getNext()) {
		if (p->getItem() == value)
			return true;
		else
			p = p->getNext();
	}
	if (p->getItem() == value)
		return true;
	else
		return false;
}

template<typename T>
void LinkedList<T>::DeleteAll() {
	Node<T>* P = Head;
	while (Head)
	{
		P = Head->getNext();
		delete Head;
		Head = P;
	}
}

template <typename T>
T* LinkedList<T>::toArray(int& count)
{
	count = 0;

	if (!Head)
		return nullptr;
	//counting the no. of items in the Stack
	Node<T>* p = Head;
	while (p)
	{
		count++;
		p = p->getNext();
	}

	T* Arr = new T[count];
	p = Head;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

template <typename T>
bool LinkedList<T>::removeOrder(T &pO)
{
	if (isEmpty())
	{
		return false;
	}
	pO = Head->getItem();
	if (Head->getNext())
	{
		Head = Head->getNext();
	}
	else
		Head = nullptr;
	return true;
}

template <>
inline Order* LinkedList<Order*>::returnOrder(ORD_TYPE type)
{
	Node<Order*>* p = Head;
	if (Head == nullptr) {
		return nullptr;
	}
	while (p)
	{
		if (p->getItem()->GetType() == type)
		{
			return p->getItem();
		}
		else
		{
			p = p->getNext();
		}
	}
	return nullptr;
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
	if (!Head)
		return true;
	else
		return false;
}


template <>
 inline void LinkedList<Order*>::deleteOrder(int oID, Order* pO)
{
	Node<Order*>* p = Head;
	Node<Order*>* np;
	if (Head == nullptr) {
		return;
	}
	if (p->getItem()->GetID() == oID) {
		pO = p->getItem();
		DeleteFirst();
		return;
	}
	while (p->getNext()) {
		if (p->getNext()->getItem()->GetID() == oID) {
			np = p->getNext();
			p->setNext(np->getNext());
			pO = np->getItem();
			delete np;
			return;
		}
		else
			p = p->getNext();
	}
	if (p->getItem()->GetID() == oID) {
		pO = p->getItem();
		DeleteLast();
		return;
	}
	else
		return;

}


template<typename T>
LinkedList<T>::~LinkedList() {
	DeleteAll();
}

