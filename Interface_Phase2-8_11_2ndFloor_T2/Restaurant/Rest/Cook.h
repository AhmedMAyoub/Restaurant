#pragma once

#include "..\Defs.h"
#include "Order.h"
#include <cstdlib>
#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	 //for each order type there is a corresponding type (VIP, Normal, Vegan)	
	int breakorders; // Number of orders a cook must prepare before taking a break
	static int NumberOfAvailablecooks;
	static int VIPAvailablecooks;
	static int NORAMALAvailablecooks;
	static int VEGANAvailablecooks;
	int NumberofCOOKS;
	//////////////////////////////Phase 2 //////////////////////////////////
	int MinSpeed; //Minimum Number Of Dishes it can prepare in one clock tick (in one timestep)
	int MaxSpeed; //Maximum Number Of Dishes it can prepare in one clock tick (in one timestep)
	int Speed; //Number Of Dishes it can prepare in one clock tick (in one timestep)
	int MinBreak; //Minimum Break Duration
	int MaxBreak; //Maximum Break Duration
	int Break; //Break Duration
	int breakFinishTime;	//finish time of break OR REST
	int finishTime;		//finish time of assigned order
	Order* AssignedOrder; //AM git
	int ordersDone = 0;
	static float InjProp;//static as probability a busy cook gets injured is the same for all cooks
	static int RstPrd;   //static as rest period is the same for all cooks
	static int InjuredCooks;
public:
	Cook();
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE) ;
	void setbreakorders(int);
	int  getbreakorders() const;
	//////////////////////////////Phase 2 //////////////////////////////////
	int Generate_between_TwoNumbers(int LastNumber, int FirstNumber); // random number generating function

	void SetMinSpeed(int);
	int  GetMinSpeed();

	void SetMaxSpeed(int);
	int  GetMaxSpeed();

	void SetSpeed(int min, int max);
	void SetXSpeed(int s);
	int GetSpeed();


	void SetMinBreak(int);
	int  GetMinBreak();

	void SetMaxBreak(int);
	int  GetMaxBreak();

	void SetBreak(int min, int max);
	int GetBreak();

	void SetBreakFinishTime(int prd, int ts);
	int GetBreakFinishTime();

	void setFinishTime(int);
	int getFinishTime();

	void setAssignedOrder(Order*);
	Order* getAssignedOrder();

	static void  SetInjProp(float);
	static float GetInjProp();

	static void SetRstPrd(int);
	static int  GetRstPrd();

	void setordersdone(int i);
	int getordersdone();

	static void SetNumberOfInjured(int);
	static int GetNumberOfInjured();


	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	void setNumberofAvailableCooks(int);
	void setVIPAvailablecooks(int);
	void setNORMALAvailablecooks(int);
	void setVEGANAvailablecooks(int);
	void setNumberofCOOKS(int);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	int getNumberofAvaialableCooks();
	int getVIPAvailablecooks();
	int getNORMALAvailablecooks();
	int getVEGANAvailablecooks();
	int getNumberofCOOKS();

};
