#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"
#include "..\Rest\Restaurant.h"

//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	
	ORD_TYPE OrdType;//order type: Normal, vegan, VIP
	int OrdSize;
	double OrdMony;	//Total order money
	int OrdID;
	int OrdArrTime;
public:
	
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType,int OSize,double OMony);

	ArrivalEvent();
	
	int    getoid();
	double getomoney();
	int    getosize();
	ORD_TYPE getotype();
	int getoarrivaltime();
	
	virtual void Execute(Restaurant *pRest);	//AM //override execute function

};

#endif