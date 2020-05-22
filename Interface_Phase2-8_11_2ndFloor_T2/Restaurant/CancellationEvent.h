#ifndef __CANCELLATION_EVENT_H_
#define __CANCELLATION_EVENT_H_


#include "Events\Event.h"
#include "..\Restaurant\Rest\Restaurant.h"

class CancellationEvent:public Event

{
	int OrdId;
public:

	CancellationEvent(); //AM
	CancellationEvent(int eTime, int oid); //AM
	int getoid();
	virtual void Execute(Restaurant* pRest); //AM	//override execute function

};
#endif