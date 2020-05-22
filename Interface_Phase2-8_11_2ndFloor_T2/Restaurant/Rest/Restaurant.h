#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancellationEvent.h"
#include "..\Generic_DS\Stack.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Generic_DS\AscPriorityQueue.h"
#include "..\Generic_DS\DescPriorityQueue.h"
#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	void FileLoadingFunction(); //SF
	void OutputFileFunction();  //SF
	LinkedList<Order*> normalOrders;
	DescPriorityQueue<Order*> VIPOrders;
	Queue<Order*> veganOrders;
	Queue<Cook*> normalCooks;
	Queue<Cook*> veganCooks;
	Queue<Cook*> VIPCooks;
	AscPriorityQueue<Order*> inServiceList;
	Queue<Order*> finishedList;
	AscPriorityQueue<Cook*> busyCookList;
	AscPriorityQueue<Cook*> breakCookList;
	AscPriorityQueue<Cook*> restCookList;
	Queue<Order*> UrgentList;
	AscPriorityQueue<Cook*> InjuredCooks;

	//
	// TODO: Add More Data Members As Needed
	//
	int timeStep;
public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	
	void Add_TO_FinishedList();
	void cooksAfterFinishing();
	void cooksAfterBreak();
	void FillDrawingList();

	void ArrivalOfOrder(int oID, ORD_TYPE oType, int oAT, int oSize, double oMoney); //AM
	void CancelOrder(int oID); //AM
	void PromoteOrder(int oID, double Exmony);   //SF
	void CheckAutoPromotion();                   //SF
	
	float Generate_Decimal_Number();

	void AssignOrders();

	void HealthEmergencyProblems();

	Queue<Order*>* sortedfinished();

	void printOnStatus();
	int calculateServiceTime(Order*, Cook*); //AM

	// TODO: Add More Member Functions As Needed
	//
	LinkedList<Order*>* getnormalOrders();
	Queue<Order*>* getveganOrders();
	DescPriorityQueue<Order*>* getVIPOrders();
	void SimulatorFunction();
	void Add_TO_UrgentList();
	void Assign_Urgent_Orders(Order*, Cook*, int, int, int);

};

#endif
