//#include "Drawing.h"


#include "Rest\Restaurant.h"


#include "GUI\GUI.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

/*

void PrintQueue(Queue<Cook> Q)
{
	Cook K;
	cout << "\nQueue contents: ";
	while (Q.dequeue(K))
	{
		cout << K.GetID() << " ";

		
		
		cout << K.getspeed() << " ";
		cout << K.getbreakduration()<<" ";
		cout << K.getbreakorders()<<" ";
		
		cout << endl;
	}
}
void PrintQueue(Queue<ArrivalEvent> Q)
{
	ArrivalEvent K;
	cout << "\nQueue contents: ";
	while (Q.dequeue(K))
	{
		cout << K.getoid() << " ";
		cout << K.getomoney();
		



		cout << endl;
	}
}
void PrintQueue(Queue<CancellationEvent> Q)
{
	CancellationEvent K;
	cout << "\nQueue contents: ";
	while (Q.dequeue(K))
	{
		cout << K.getoid() << " ";
		



		cout << endl;
	}
}

*/



int main()
{

	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();

	delete pRest;
	return 0;
}

