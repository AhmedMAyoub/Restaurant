#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Node.h"
#include<iostream>
using namespace std;

template <typename T>
class PriorityQueue {

private:

	Node<T>* frontptr;
	Node<T>* backptr;

public:

	PriorityQueue();
	bool isEmpty();
	bool enqueue(const T& NewEntry, int Priority);
	bool dequeue(T& FrontEntry);
	bool peekFront(T& FrontEntry);
	T* toArray(int& count);

	void Print() {

		Node <T>* G = frontptr;
		while (G) {

			cout << G->getItem() << " ";
			G = G->getNext();

		}
	}

	~PriorityQueue();
};

template <typename T>
PriorityQueue<T>::PriorityQueue() {

	frontptr = nullptr;
	backptr = nullptr;
}

template <typename T>
bool PriorityQueue<T>::enqueue(const T& NewEntry, int Priority) {

	Node <T>* ptr = new Node<T>(NewEntry);
	ptr->setPriorityNumber(Priority);

	if (isEmpty()) {

		backptr = ptr;
		frontptr = ptr;
		return true;
	}

	Node <T>* G = frontptr;

	if (!G->getNext()) {

		if (G->getPriorityNumber() > ptr->getPriorityNumber()) {

			ptr->setNext(G);
			frontptr = ptr;
			return true;
		}
		else if (G->getPriorityNumber() <= ptr->getPriorityNumber()) {

			G->setNext(ptr);
		}
		return true;
	}

	if (frontptr->getPriorityNumber() > ptr->getPriorityNumber()) {

		ptr->setNext(frontptr);
		frontptr = ptr;
		return true;
	}

	else if (frontptr->getPriorityNumber() == ptr->getPriorityNumber()) {

		Node<T>* H = frontptr;
		while (H->getNext()) {
			if (frontptr->getPriorityNumber() == H->getNext()->getPriorityNumber()) {

				H = H->getNext();
			}
			else {

				break;
			}

		}
		ptr->setNext(H->getNext());
		H->setNext(ptr);
		return true;
	}
	else if (backptr->getPriorityNumber() <= ptr->getPriorityNumber()) {

		backptr->setNext(ptr);
		backptr = ptr;
		return true;
	}
	while (G->getNext()) {

		if (G->getPriorityNumber()<ptr->getPriorityNumber() && G->getNext()->getPriorityNumber()> ptr->getPriorityNumber()) {

			ptr->setNext(G->getNext());
			G->setNext(ptr);
			return true;
		}
		else if (G->getPriorityNumber() == ptr->getPriorityNumber()) {

			Node<T>* H = G;
			while (H->getNext()) {
				if (G->getPriorityNumber() == H->getNext()->getPriorityNumber()) {

					H = H->getNext();
				}
				else {

					break;
				}

			}

			ptr->setNext(H->getNext());
			H->setNext(ptr);
			return true;
		}
		else if (G->getNext()->getPriorityNumber() == ptr->getPriorityNumber()) {

			Node<T>* H = G->getNext();
			while (H->getNext()) {
				if (G->getNext()->getPriorityNumber() == H->getNext()->getPriorityNumber()) {

					H = H->getNext();
				}
				else {

					break;
				}

			}

			ptr->setNext(H->getNext());
			H->setNext(ptr);
			return true;
		}
		else {

			G = G->getNext();
		}
		//}
	}
}

template <typename T>
bool PriorityQueue<T>::isEmpty() {

	if (frontptr == nullptr)
		return true;
	else
		return false;
}

template<typename T>
bool PriorityQueue<T>::dequeue(T& frontEntry) {

	if (isEmpty())
		return false;

	Node<T>* Ptr = frontptr;
	frontEntry = frontptr->getItem();
	frontptr = frontptr->getNext();

	if (Ptr == backptr)
		backptr = nullptr;

	delete Ptr;
	return true;
}

template <typename T>
bool PriorityQueue<T>::peekFront(T & frontEntry) {

	if (isEmpty())
		return false;

	frontEntry = frontptr->getItem();
	return true;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {

	backptr = nullptr;

	while (frontptr) {

		Node<T>* ptr = frontptr;
		frontptr = frontptr->getNext();
		delete ptr;
	}

	frontptr = nullptr;
}

template <typename T>
T* PriorityQueue<T>::toArray(int& count) {

	count = 0;

	if (!frontptr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontptr;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = frontptr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;



}
#endif 

