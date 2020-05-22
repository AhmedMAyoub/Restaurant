#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\CancellationEvent.h"
#include "..\PromotionEvent.h"
#include <fstream>
#include <iostream>
#include <iomanip>
////////////////////
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds


void Restaurant::FileLoadingFunction()                                    //SF
{
	
	//Phase 1 
	int N, G, V;      // Number Of Cooks Of Different Types
	int BO;           
	int AutoP;        // Number of ticks after which an order is automatically promoted to VIP
	int	M;            // Number Of Events 
	int TS, ID, SIZE; // Order Info
	double MONY; 
	char EventType, TYP; // Event Type And Order Type
	////////////////////////Phase 2 //////////////////////
	int SN_min, SN_max, SG_min, SG_max, SV_min, SV_max; //Speed Range Of Each Cook Type
	int BN_min, BN_max, BG_min, BG_max, BV_min, BV_max; //Break Range Of Each Cook Type
	float InjProp;     
	int RstPrd;      
	int VIP_WT;      //Number of ticks after which a VIP order is considered urgent
	double ExMony;
	pGUI->UpdateInterface();

	pGUI->PrintMessage("Please Enter File Name:");

	ifstream fin(pGUI->GetString2());
	
	fin >> N >> G >> V;
	fin >> SN_min >> SN_max >> SG_min >> SG_max >> SV_min >> SV_max;
	fin >> BO >> BN_min >> BN_max >> BG_min >> BG_max >> BV_min >> BV_max;
	fin >> InjProp >> RstPrd;
	fin >> AutoP >> VIP_WT;
	fin >> M;
	
	Cook* ptr = new Cook;
	ptr->SetInjProp(InjProp);
	ptr->SetRstPrd(RstPrd);
	delete ptr;

	Order* op = nullptr;
	op->setPromotiontime(AutoP);
	op->set_VIP_WT(VIP_WT);
	delete op;


	int idcount = 1;
	for (int i = 0; i < N; i++)
	{

		Cook * nptr = new Cook;
		nptr->setID(idcount);
		idcount++;
		nptr->setType(TYPE_NRM);
		nptr->setbreakorders(BO);
		/////////////////////////Phase 2 /////////////////////
		nptr->SetMinSpeed(SN_min);
		nptr->SetMaxSpeed(SN_max);
		nptr->SetSpeed(SN_min, SN_max);
		nptr->SetMinBreak(BN_min);
		nptr->SetMaxBreak(BN_max);
		nptr->SetBreak(BN_min, BN_max);
		normalCooks.enqueue(nptr);
		nptr->setNORMALAvailablecooks((nptr->getNORMALAvailablecooks())+1);
		nptr->setNumberofAvailableCooks(nptr->getNumberofAvaialableCooks() + 1);
		
	

	}
	
	for (int i = 0; i < G; i++)
	{
		Cook* nptr = new Cook;
		nptr->setType(TYPE_VGAN);
		nptr->setID(idcount);
		idcount++;
		nptr->setbreakorders(BO);
		/////////////////////////Phase 2/////////////////////
		nptr->SetMinSpeed(SG_min);
		nptr->SetMaxSpeed(SG_max);
		nptr->SetSpeed(SG_min, SG_max);
		nptr->SetMinBreak(BG_min);
		nptr->SetMaxBreak(BG_max);
		nptr->SetBreak(BG_min, BG_max);
		veganCooks.enqueue(nptr);
		nptr->setVEGANAvailablecooks((nptr->getVEGANAvailablecooks()) + 1);
		nptr->setNumberofAvailableCooks(nptr->getNumberofAvaialableCooks() + 1);
		
	}

	
	for (int i = 0; i < V; i++)
	{
		Cook* nptr = new Cook;
		nptr->setType(TYPE_VIP);
		nptr->setID(idcount);
		idcount++;
		nptr->setbreakorders(BO);
		/////////////////////////Phase 2 /////////////////////
		nptr->SetMinSpeed(SV_min);
		nptr->SetMaxSpeed(SV_max);
		nptr->SetSpeed(SV_min, SV_max);
		nptr->SetMinBreak(BV_min);
		nptr->SetMaxBreak(BV_max);
		nptr->SetBreak(BV_min, BV_max);
		VIPCooks.enqueue(nptr);
		nptr->setVIPAvailablecooks((nptr->getVIPAvailablecooks()) + 1);
		nptr->setNumberofAvailableCooks(nptr->getNumberofAvaialableCooks() + 1);
		
	}

	ORD_TYPE OD;

	for (int i = 0; i < M; i++)
	{
		fin >> EventType;
		if (EventType == 'R')
		{
			fin >> TYP >> TS >> ID >> SIZE >> MONY;
			if (TYP == 'N')
			{
				OD = TYPE_NRM;
			}
			else if (TYP == 'G')
			{
				OD = TYPE_VGAN;
			}
			else
			{
				OD = TYPE_VIP;
			}

			ArrivalEvent* nptr = new ArrivalEvent(TS, ID, OD, SIZE, MONY);
			EventsQueue.enqueue(nptr);


		}
		else if (EventType == 'X')
		{
			fin >> TS >> ID;
			CancellationEvent* nptr = new CancellationEvent(TS, ID);
			EventsQueue.enqueue(nptr);

		}
		else
		{
			fin >> TS >> ID >> ExMony;
			PromotionEvent* nptr = new PromotionEvent(TS, ID, ExMony);
			EventsQueue.enqueue(nptr);
		}
	}
	
}
void Restaurant::OutputFileFunction()                                               //SF
{
	ofstream fout("Out.txt");
	fout << "FT   ID   AT   WT   ST "; 
	fout << endl;
	
	int count;  //Total Number OF Orders
	Order** OPP = finishedList.toArray(count); 
	Order* OP = nullptr;
	OP->PrintArr(count, OPP);
	cout << endl;

	//Order ** finishedlistsorted=OP->SortSrvtime(count, OPP);    // this line Causes  a heap realted problem
	//OP->PrintArr(count, finishedlistsorted);
	
	int TotatWaitingTime = 0;
	int	TotalInserviceTime = 0;
	
	for (int i = 0; i < count; i++)
	{
		Order* O = OPP[i];
		//Order*  O =finishedlistsorted[i];     
		fout << O->getFinishedtime() << "    ";
		fout << O->GetID() << "    ";
		fout << O->getArrivaltime() << "    ";
		fout << O->getWaitingTime() << "    ";    
		fout << O->getSevicetime() << "     ";   
		fout << endl;
		TotatWaitingTime += O->getWaitingTime();
		TotalInserviceTime += O->getSevicetime();

	}
	fout << "Orders:" << count << " " << "[" << "Norm:" << OP->getFnormal() << "," << "Veg:" << OP->getFvegan() << "," << "VIP:" << OP->getFvip() << "]";
	fout << endl;
	int n, vip, vg;
	normalCooks.toArray(n);  // Number OF Normal Cooks
	veganCooks.toArray(vg);  // Number OF Vegan  Cooks
	VIPCooks.toArray(vip);   // Number OF VIP    Cooks
	Cook* CP = nullptr;
	int total = n + vg + vip;//Total Number OF Cooks
	fout << "Cooks:" << total << " " << "[" << "Norm:" << n << "," << "Veg:" << vg << "," << "VIP:" << vip<< "," << "injured:"<<CP->GetNumberOfInjured()<<"]";
	fout << endl;
	float AvgWaitingTime = (float)TotatWaitingTime /(float) count;
	float AvgInserviceTime = (float)TotalInserviceTime /(float) count;
	fout << "Avg Wait=" <<fixed<< setprecision(2)<<AvgWaitingTime << ",  " << "Avg Serv=" <<fixed<< setprecision(2)<< AvgInserviceTime;
	fout << endl;
	int TotalNormOrders = OP->getFnormal() + OP->getAutoPromoted();
	float calcAutoprom = (((float)OP->getAutoPromoted() /(float) TotalNormOrders )* 100);
	fout << "Urgent orders:" << OP->GetNumberOfUrgent()<<" ,"<< "Auto-Promoted:" << (int)calcAutoprom<< "%";
	
}


Restaurant::Restaurant() 
{
	pGUI = NULL;
	timeStep = 1;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		SimulatorFunction(MODE_INTR);
		break;
	case MODE_STEP:
		SimulatorFunction(MODE_STEP);
		break;
	case MODE_SLNT:
		SimulatorFunction(MODE_SLNT);
		break;
	
	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


/*
LinkedList<Order*>* Restaurant::getnormalOrders()
{
	return &normalOrders;
}

Queue<Order*>* Restaurant::getveganOrders()
{
	return &veganOrders;
}

PriorityQueue<Order*>* Restaurant::getVIPOrders()
{
	return &VIPOrders;
}
*/
Restaurant::~Restaurant()
{
		if (pGUI)
			delete pGUI;
}


void Restaurant::FillDrawingList() //AM
{
	int size=0;
	Order** orderArrayToDraw;
	orderArrayToDraw = VIPOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(orderArrayToDraw[i]);
	}
	orderArrayToDraw = normalOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(orderArrayToDraw[i]);
	}
	orderArrayToDraw = veganOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(orderArrayToDraw[i]);
	}
	Cook** cookArrayToDraw;
	cookArrayToDraw = VIPCooks.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(cookArrayToDraw[i]);
	}
	cookArrayToDraw = normalCooks.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(cookArrayToDraw[i]);
	}
	cookArrayToDraw = veganCooks.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(cookArrayToDraw[i]);
	}
	orderArrayToDraw = inServiceList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(orderArrayToDraw[i]);
	}
	orderArrayToDraw = finishedList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pGUI->AddToDrawingList(orderArrayToDraw[i]);
	}
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);

}

void Restaurant::Add_TO_FinishedList() {					//MM

	if (inServiceList.isEmpty()) {

		return;
	}
	else {

		Order* ptr;
		inServiceList.peekFront(ptr);
		while (ptr->getFinishedtime() == timeStep)
		{

			inServiceList.dequeue(ptr);
			ptr->setStatus(DONE);
			finishedList.enqueue(ptr);
			if (ptr->GetType() == TYPE_NRM)                         //SF
				ptr->setFnormal(ptr->getFnormal() + 1);             //SF
			else if (ptr->GetType() == TYPE_VGAN)                   //SF
				ptr->setFvegan(ptr->getFvegan() + 1);               //SF
			else                                                    //SF
				ptr->setFvip(ptr->getFvip() + 1);                   //SF


			if (inServiceList.isEmpty()) {

				return;
			}

			inServiceList.peekFront(ptr);
		}
	}
}


void Restaurant::SimulatorFunction(PROG_MODE MODE) //AM
{
	FileLoadingFunction();
	while (!EventsQueue.isEmpty() || !normalOrders.isEmpty() || !veganOrders.isEmpty() || !VIPOrders.isEmpty() || !inServiceList.isEmpty())
	{
		pGUI->ResetDrawingList();
		
		ExecuteEvents(timeStep);
		Order* pO=nullptr;
		AssignOrders();									    //Assigning Orders to cooks if available
		
		Add_TO_FinishedList();							    // Move finished orders at this timestep to finishedlist
		cooksAfterFinishing();					            // Move cooks to their list or break or (not implemented rest)
		CheckAutoPromotion();                           //SF 
		if (MODE != MODE_SLNT)                          //SF
		{
			FillDrawingList();
			pGUI->UpdateInterface();
			printOnStatus( MODE);								//Print on status bar
		}
		if (MODE == MODE_INTR)                          //SF
		{
			pGUI->waitForClick();
		}
		else if (MODE == MODE_STEP)
		{
			Sleep(1000);                 //Edited
		}
		CooksAssigned = Queue<Cook*>();               //SF
		timeStep++;
	}
	
	OutputFileFunction(); //SF
}

void Restaurant::CancelOrder(int oID) //AM phase 1
{
	Order** Arr;
	int count = 0;
	Arr = normalOrders.toArray(count);
	for (int i = 0; i < count; i++)
	{
		if (Arr[i]->GetID() == oID)
		{
			normalOrders.deleteOrder(oID, Arr[i]);
			Arr[i]->setWOrders(Arr[i]->getWOrders() - 1);
			Arr[i]->setWnormal(Arr[i]->getWnormal() - 1);
		}
	}
}

void Restaurant::ArrivalOfOrder(int oID, ORD_TYPE oType, int oAT, int oSize, double oMoney) //AM phase 1
{
	Order *pO = new Order(oID, oType, oAT, oSize, oMoney);
	if (oType == TYPE_NRM)
	{
		
		normalOrders.InsertEnd(pO);
		pO->setWnormal((pO->getWnormal()) + 1);
		pO->setWOrders((pO->getWOrders()) + 1);
	}
	else if (oType == TYPE_VGAN)
	{
		
		veganOrders.enqueue(pO);
		pO->setWvegan((pO->getWvegan()) + 1);
		pO->setWOrders((pO->getWOrders()) + 1);
	}
	else
	{
		
		VIPOrders.enqueue(pO, pO->getPriority());
		pO->setWvip((pO->getWvip()) + 1);
		pO->setWOrders((pO->getWOrders()) + 1);
	}
}


void Restaurant::PromoteOrder(int oID, double Exmony)      //SF
{
	Order** Arr;
	int count = 0;
	Arr = normalOrders.toArray(count);
	for (int i = 0; i < count; i++)
	{
		if (Arr[i]->GetID()==oID)
		{
			normalOrders.deleteOrder(oID,Arr[i]);
			Arr[i]->setWnormal(Arr[i]->getWnormal() - 1);

			Arr[i]->setEXmoney(Exmony);
			Arr[i]->setTotalMoney(Arr[i]->getTotalMoney() + Arr[i]->getEXmoney());
			Arr[i]->SetType(TYPE_VIP);
			Arr[i]->calculateVIPPriority();
			VIPOrders.enqueue(Arr[i], Arr[i]->getPriority());
			Arr[i]->setWvip(Arr[i]->getWvip() + 1);
			
		}
	}
}

void Restaurant::CheckAutoPromotion()         //SF
{
	Order** Arr;
	int count = 0;
	Arr = normalOrders.toArray(count);
	for (int i = 0; i < count; i++)
	{

		if (Arr[i]->Calcualte_Waiting_Time(timeStep, Arr[i]->getArrivaltime()) >= Arr[i]->getPromotiontime())
		{
			PromoteOrder(Arr[i]->GetID(), 0);
			Arr[i]->setAutoPromoted(Arr[i]->getAutoPromoted() + 1);
			
		}
	}

}

void Restaurant::Assign_Urgent_Orders(Order* pO, Cook* pC, int FT, int ST, int WT) {


	while (UrgentList.peekFront(pO) && (VIPCooks.peekFront(pC) || normalCooks.peekFront(pC) || veganCooks.peekFront(pC) || breakCookList.peekFront(pC) || restCookList.peekFront(pC))) {

		if (VIPCooks.peekFront(pC)) {

			UrgentList.dequeue(pO);
			pO->setStatus(SRV);
			WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
			ST = calculateServiceTime(pO, pC);
			FT = pO->getArrivaltime() + WT + ST;
			pO->setWaitingTime(WT);
			pO->setServicetime(ST);
			pO->setFinishedtime(FT);
			inServiceList.enqueue(pO, pO->getFinishedtime());
			pO->setWvip((pO->getWvip()) - 1);
			pO->setWOrders((pO->getWOrders()) - 1);
			VIPCooks.dequeue(pC);
			pC->setVIPAvailablecooks(pC->getVIPAvailablecooks() - 1);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() - 1);
			pC->setAssignedOrder(pO);
			pC->setFinishTime(timeStep + ST);
			busyCookList.enqueue(pC, pC->getFinishTime());
			CooksAssigned.enqueue(pC);
		}

		else if (normalCooks.peekFront(pC)) {

			UrgentList.dequeue(pO);
			pO->setStatus(SRV);
			WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
			ST = calculateServiceTime(pO, pC);
			FT = pO->getArrivaltime() + WT + ST;
			pO->setWaitingTime(WT);
			pO->setServicetime(ST);
			pO->setFinishedtime(FT);
			inServiceList.enqueue(pO, pO->getFinishedtime());
			pO->setWvip((pO->getWvip()) - 1);
			pO->setWOrders((pO->getWOrders()) - 1);
			normalCooks.dequeue(pC);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() - 1);
			pC->setNORMALAvailablecooks(pC->getNORMALAvailablecooks() - 1);
			pC->setAssignedOrder(pO);
			pC->setFinishTime(timeStep + ST);
			busyCookList.enqueue(pC, pC->getFinishTime());
			CooksAssigned.enqueue(pC);
		}

		else if (veganCooks.peekFront(pC)) {

			UrgentList.dequeue(pO);
			pO->setStatus(SRV);
			WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
			ST = calculateServiceTime(pO, pC);
			FT = pO->getArrivaltime() + WT + ST;
			pO->setWaitingTime(WT);
			pO->setServicetime(ST);
			pO->setFinishedtime(FT);
			inServiceList.enqueue(pO, pO->getFinishedtime());
			pO->setWvip((pO->getWvip()) - 1);
			pO->setWOrders((pO->getWOrders()) - 1);
			veganCooks.dequeue(pC);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() - 1);
			pC->setVEGANAvailablecooks(pC->getVEGANAvailablecooks() - 1);
			pC->setAssignedOrder(pO);
			pC->setFinishTime(timeStep + ST);
			busyCookList.enqueue(pC, pC->getFinishTime());
			CooksAssigned.enqueue(pC);
		}

		else if (breakCookList.peekFront(pC)) {

			UrgentList.dequeue(pO);
			pO->setStatus(SRV);
			WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
			ST = calculateServiceTime(pO, pC);
			FT = pO->getArrivaltime() + WT + ST;
			pO->setWaitingTime(WT);
			pO->setServicetime(ST);
			pO->setFinishedtime(FT);
			inServiceList.enqueue(pO, pO->getFinishedtime());
			pO->setWvip((pO->getWvip()) - 1);
			pO->setWOrders((pO->getWOrders()) - 1);
			breakCookList.dequeue(pC);
			pC->setAssignedOrder(pO);
			pC->setFinishTime(timeStep + ST);
			busyCookList.enqueue(pC, pC->getFinishTime());
			CooksAssigned.enqueue(pC);
		}

		else if (restCookList.peekFront(pC)) {


			UrgentList.dequeue(pO);
			pO->setStatus(SRV);
			WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
			ST = calculateServiceTime(pO, pC);
			FT = pO->getArrivaltime() + WT + ST;
			pO->setWaitingTime(WT);
			pO->setServicetime(ST);
			pO->setFinishedtime(FT);
			inServiceList.enqueue(pO, pO->getFinishedtime());
			pO->setWvip((pO->getWvip()) - 1);
			pO->setWOrders((pO->getWOrders()) - 1);
			restCookList.dequeue(pC);
			pC->setAssignedOrder(pO);
			pC->setFinishTime(timeStep + ST);
			busyCookList.enqueue(pC, pC->getFinishTime());
			CooksAssigned.enqueue(pC);
		}
	}
}


void Restaurant::AssignOrders() //AM
{
	Order* pO;
	Cook* pC;
	int FT = 0;
	int ST = 0;
	int WT = 0;

	Assign_Urgent_Orders(pO, pC, FT, ST, WT);

	while (VIPOrders.peekfront(pO) && (VIPCooks.peekFront(pC) || normalCooks.peekFront(pC) || veganCooks.peekFront(pC)))
	{
		if (VIPCooks.peekFront(pC))
		{
			VIPOrders.dequeue(pO);
			pO->setStatus(SRV);
			WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
			ST = calculateServiceTime(pO, pC);
			FT = pO->getArrivaltime() + WT + ST;
			pO->setWaitingTime(WT);
			pO->setServicetime(ST);
			pO->setFinishedtime(FT);
			inServiceList.enqueue(pO, pO->getFinishedtime());
			pO->setWvip((pO->getWvip()) - 1);
			pO->setWOrders((pO->getWOrders()) - 1);
			VIPCooks.dequeue(pC);
			pC->setVIPAvailablecooks(pC->getVIPAvailablecooks() - 1);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() - 1);
			pC->setAssignedOrder(pO);
			pC->setFinishTime(timeStep + ST);
			busyCookList.enqueue(pC, pC->getFinishTime());
			CooksAssigned.enqueue(pC);     //SF
		}
		else if (normalCooks.peekFront(pC))
		{
			VIPOrders.dequeue(pO);
			pO->setStatus(SRV);
			WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
			ST = calculateServiceTime(pO, pC);
			FT = pO->getArrivaltime() + WT + ST;
			pO->setWaitingTime(WT);
			pO->setServicetime(ST);
			pO->setFinishedtime(FT);
			inServiceList.enqueue(pO, pO->getFinishedtime());
			pO->setWvip((pO->getWvip()) - 1);
			pO->setWOrders((pO->getWOrders()) - 1);
			normalCooks.dequeue(pC);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() - 1);
			pC->setNORMALAvailablecooks(pC->getNORMALAvailablecooks() - 1);
			pC->setAssignedOrder(pO);
			pC->setFinishTime(timeStep + ST);
			busyCookList.enqueue(pC, pC->getFinishTime());
			CooksAssigned.enqueue(pC);     //SF


		}
		else if (veganCooks.peekFront(pC))
		{
			VIPOrders.dequeue(pO);
			pO->setStatus(SRV);
			WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
			ST = calculateServiceTime(pO, pC);
			FT = pO->getArrivaltime() + WT + ST;
			pO->setWaitingTime(WT);
			pO->setServicetime(ST);
			pO->setFinishedtime(FT);
			inServiceList.enqueue(pO, pO->getFinishedtime());
			pO->setWvip((pO->getWvip()) - 1);
			pO->setWOrders((pO->getWOrders()) - 1);
			veganCooks.dequeue(pC);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() - 1);
			pC->setVEGANAvailablecooks(pC->getVEGANAvailablecooks() - 1);
			pC->setAssignedOrder(pO);
			pC->setFinishTime(timeStep + ST);
			busyCookList.enqueue(pC, pC->getFinishTime());
			CooksAssigned.enqueue(pC);     //SF


		}
	}
	while (veganOrders.peekFront(pO) && veganCooks.peekFront(pC))
	{
		veganOrders.dequeue(pO);
		pO->setStatus(SRV);
		WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
		ST = calculateServiceTime(pO, pC);
		FT = pO->getArrivaltime() + WT + ST;
		pO->setWaitingTime(WT);
		pO->setServicetime(ST);
		pO->setFinishedtime(FT);
		inServiceList.enqueue(pO, pO->getFinishedtime());
		pO->setWvegan((pO->getWvegan()) - 1);
		pO->setWOrders((pO->getWOrders()) - 1);
		veganCooks.dequeue(pC);
		pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() - 1);
		pC->setVEGANAvailablecooks(pC->getVEGANAvailablecooks() - 1);
		pC->setAssignedOrder(pO);
		pC->setFinishTime(timeStep + ST);
		busyCookList.enqueue(pC, pC->getFinishTime());
		CooksAssigned.enqueue(pC);     //SF


	}
	while (!normalOrders.isEmpty() && (normalCooks.peekFront(pC) || VIPCooks.peekFront(pC)))
	{
		if (normalCooks.peekFront(pC))
		{
			normalOrders.removeOrder(pO);
			pO->setStatus(SRV);
			WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
			ST = calculateServiceTime(pO, pC);
			FT = pO->getArrivaltime() + WT + ST;
			pO->setWaitingTime(WT);
			pO->setServicetime(ST);
			pO->setFinishedtime(FT);
			inServiceList.enqueue(pO, pO->getFinishedtime());
			pO->setWnormal((pO->getWnormal()) - 1);
			pO->setWOrders((pO->getWOrders()) - 1);
			normalCooks.dequeue(pC);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() - 1);
			pC->setNORMALAvailablecooks(pC->getNORMALAvailablecooks() - 1);
			pC->setAssignedOrder(pO);
			pC->setFinishTime(timeStep + ST);
			busyCookList.enqueue(pC, pC->getFinishTime());
			CooksAssigned.enqueue(pC);     //SF

			

		}
		else
		{
			normalOrders.removeOrder(pO);
			pO->setStatus(SRV);
			WT = pO->Calcualte_Waiting_Time(timeStep, pO->getArrivaltime());
			ST = calculateServiceTime(pO, pC);
			FT = pO->getArrivaltime() + WT + ST;
			pO->setWaitingTime(WT);
			pO->setServicetime(ST);
			pO->setFinishedtime(FT);
			inServiceList.enqueue(pO, pO->getFinishedtime());
			pO->setWnormal((pO->getWnormal()) - 1);
			pO->setWOrders((pO->getWOrders()) - 1);
			VIPCooks.dequeue(pC);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() - 1);
			pC->setVIPAvailablecooks(pC->getVIPAvailablecooks() - 1);
			pC->setAssignedOrder(pO);
			pC->setFinishTime(timeStep + ST);
			busyCookList.enqueue(pC, pC->getFinishTime());
			CooksAssigned.enqueue(pC);     //SF


		}
	}
}

float Restaurant::Generate_Decimal_Number() 
{
	srand((unsigned)time(NULL));
	float RandomNumber = (float)rand() / RAND_MAX;
	return RandomNumber;
}

void Restaurant::printOnStatus(PROG_MODE MODE) //AM
{
	

	Order* pO;
	Cook cook;
	pGUI->PrintMessage("TimeStep: " + to_string(timeStep));
	string N = "     N: ";
	string VIP = "     VIP: ";
	string Veg = "     Vegan: ";
	pGUI->PrintMessage("Number of waiting Orders:  " + to_string(pO->getWOrders()) + N + to_string(pO->getWnormal()) + VIP + to_string(pO->getWvip()) + Veg + to_string(pO->getWvegan()));						//to_string(pO->getWnormal())
	pGUI->PrintMessage("Number of availabe cooks:  " + to_string(cook.getNumberofAvaialableCooks()) + N + to_string(cook.getNORMALAvailablecooks()) + VIP + to_string(cook.getVIPAvailablecooks()) + Veg + to_string(cook.getVEGANAvailablecooks()));
	PrintAssigned(CooksAssigned);
	int TotalFinishedOrders = pO->getFnormal() + pO->getFvegan() + pO->getFvip();
	pGUI->PrintMessage("Number of Finished Orders:  " + to_string(TotalFinishedOrders )+ N + to_string(pO->getFnormal()) + VIP + to_string(pO->getFvip()) + Veg + to_string(pO->getFvegan()));
	if (MODE==MODE_INTR)
	{
		pGUI->PrintMessage("Please Click Mouse to go to next timestep");
	}
}
void Restaurant::PrintAssigned(Queue <Cook*> CooksAssigned)
{

	int count;
	Cook** bl = CooksAssigned.toArray(count);
	for(int i=0;i<count;i++)
	{
		Cook* C = bl[i];
		Order* O = bl[i]->getAssignedOrder();

		if (C && O)
		{
			int CookID = C->GetID();
			ORD_TYPE CookType = C->GetType();
			string CookTypeChar;
			if (CookType == TYPE_NRM)
			{
				CookTypeChar = 'N';
			}
			else if (CookType == TYPE_VGAN)
			{
				CookTypeChar = 'G';
			}
			else
			{
				CookTypeChar = 'V';
			}


			int OrderID = O->GetID();
			ORD_TYPE OrderType = O->GetType();
			string OrderTypeChar;
			if (OrderType == TYPE_NRM)
			{
				OrderTypeChar = 'N';
			}
			else if (OrderType == TYPE_VGAN)
			{
				OrderTypeChar = 'G';
			}
			else
			{
				OrderTypeChar = 'V';
			}

			pGUI->PrintMessage( CookTypeChar + to_string(CookID)+ "(" + OrderTypeChar + to_string(OrderID) + ")" + "   ");
		}

	}
}
/*
if (normalOrders.removeOrder(pO))
{
	pO->setStatus(SRV);
	pO->setServicetime(timeStep);  //SF
	inServiceList.InsertEnd(pO);
	pO->setWnormal((pO->getWnormal()) - 1);
	pO->setWOrders((pO->getWOrders()) - 1);
}
if (VIPOrders.dequeue(pO))
{
	pO->setStatus(SRV);
	pO->setServicetime(timeStep);  //SF
	inServiceList.InsertEnd(pO);
	pO->setWvip((pO->getWvip()) - 1);
	pO->setWOrders((pO->getWOrders()) - 1);
}

if (veganOrders.dequeue(pO))
{
	pO->setStatus(SRV);
	pO->setServicetime(timeStep);    //SF
	inServiceList.InsertEnd(pO);
	pO->setWvegan((pO->getWvegan()) - 1);
	pO->setWOrders((pO->getWOrders()) - 1);
}
*/

void Restaurant::Add_TO_UrgentList() {

	if (VIPOrders.isEmpty()) {

		return;
	}
	else {

		DescPriorityQueue<Order*> UrgentOrders = VIPOrders.ReturnQueue(timeStep);

		if (UrgentOrders.isEmpty()) {

			return;
		}

		while (!UrgentOrders.isEmpty()) {

			Order* ptr;
			UrgentOrders.dequeue(ptr);
			UrgentList.enqueue(ptr);
			ptr->SetNumberofUrgent(ptr->GetNumberOfUrgent() + 1); //SF

		}

	}

}



int Restaurant::calculateServiceTime(Order* pO, Cook* pC)
{
	int serviceTime = (pO->getOSize()) / pC->GetSpeed();
	return serviceTime;
}

void Restaurant::cooksAfterFinishing()			//AM, still part manar on injured not implemented
{
	if (busyCookList.isEmpty())
	{
		return;
	}
	Cook* pC;
	busyCookList.peekFront(pC);
	while (pC->getFinishTime() == timeStep && !busyCookList.isEmpty())
	{
		busyCookList.dequeue(pC);
		CooksAssigned.dequeue(pC);    //SF
		pC->setordersdone(pC->getordersdone() + 1);
		if (pC->getordersdone() == pC->getbreakorders())
		{
			pC->setordersdone(0);
			breakCookList.enqueue(pC, pC->GetBreak());
		}
		else if (pC->GetType() == TYPE_VIP)
		{
			VIPCooks.enqueue(pC);
			pC->setVIPAvailablecooks(pC->getVIPAvailablecooks() + 1);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() + 1);
		}
		else if (pC->GetType() == TYPE_VGAN)
		{
			veganCooks.enqueue(pC);
			pC->setVEGANAvailablecooks(pC->getVEGANAvailablecooks() + 1);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() + 1);
		}
		else if (pC->GetType() == TYPE_NRM)
		{
			normalCooks.enqueue(pC);
			pC->setNORMALAvailablecooks(pC->getNORMALAvailablecooks() + 1);
			pC->setNumberofAvailableCooks(pC->getNumberofAvaialableCooks() + 1);
		}
		busyCookList.peekFront(pC);
	}
	if (InjuredCooks.isEmpty())
	{
		return;
	}
	InjuredCooks.peekFront(pC);
	while (pC->getFinishTime() == timeStep && !InjuredCooks.isEmpty())
	{
		InjuredCooks.dequeue(pC);
		restCookList.enqueue(pC, pC->GetRstPrd());
		InjuredCooks.peekFront(pC);
	}
}

void Restaurant::HealthEmergencyProblems() {
	Cook* C = new Cook();
	busyCookList.peekFront(C);
	float R = Generate_Decimal_Number();
	if (R <= C->GetInjProp()) {
		int OGfinish = C->getAssignedOrder()->getArrivaltime() + C->getAssignedOrder()->getWaitingTime() + calculateServiceTime(C->getAssignedOrder(), C);
		int remaining = OGfinish - timeStep;
		int newsize = remaining * C->GetSpeed();
		int servprev = C->getAssignedOrder()->getOSize() - newsize;
		servprev = servprev / C->GetSpeed();
		C->getAssignedOrder()->setOSize(newsize);
		C->SetHalfSpeed(C->GetSpeed());
		int newserv = calculateServiceTime(C->getAssignedOrder(), C);
		C->getAssignedOrder()->setServicetime(newserv + servprev);
		int newfinish = C->getAssignedOrder()->getArrivaltime() + C->getAssignedOrder()->getWaitingTime() + C->getAssignedOrder()->getSevicetime();
		C->getAssignedOrder()->setFinishedtime(newfinish);
		inServiceList.ReArrange(C->getAssignedOrder(), newfinish);
		int finish_cook = calculateServiceTime(C->getAssignedOrder(), C) + timeStep;
		busyCookList.dequeue(C);
		CooksAssigned.dequeue(C);    //SF

		InjuredCooks.enqueue(C, finish_cook);
		C->SetNumberOfInjured(C->GetNumberOfInjured() + 1);//SF
	}
}