#ifndef _NODE
#define _NODE

//First let's declare a single node in the list
template<typename T>
class Node
{
private:
	T item;	// A data item (can be any complex sturcture)
	Node<T>* next;	// Pointer to next node
	int PriorityNumber;// To Enqueue a node in the queue according to its priority 
public:

	Node() //default constructor
	{
		next = nullptr;
	}

	Node(T newItem) //non-default constructor
	{
		item = newItem;
		next = nullptr;

	}

	void setItem(T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext

	T getItem() 
	{
		return item;
	} // end getItem

	Node<T>* getNext() 
	{
		return next;
	}

	void setPriorityNumber(int a) {

		PriorityNumber = a;
	}

	int getPriorityNumber()  {


		return PriorityNumber;
	}
}; // end Node

#endif	
