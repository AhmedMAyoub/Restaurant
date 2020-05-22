#ifndef __Promotion_EVENT_H_
#define __Promotion_EVENT_H_

#include "Events\Event.h"
#include "Rest\Restaurant.h"

//class for the arrival event
class PromotionEvent : public Event
{
	int OrdID;
	int OrdArrTime;
	double ExMony;  //Extra money the customer paid for promotion
public:

	PromotionEvent(int eTime, int oID, double exMoney) ;
	PromotionEvent();
	int    getoid();
	double getoexmoney();
	int    getoarrivaltime();

	virtual void Execute(Restaurant *pRest);	
};

#endif