#include "PromotionEvent.h"

PromotionEvent::PromotionEvent() :Event(0, 0)
{

}
PromotionEvent::PromotionEvent(int oTime, int oid, double exMoney) : Event(oTime, oid)
{
	OrderID = oid;
	ExMony = exMoney;
}
void PromotionEvent::Execute(Restaurant* pRest)
{
	pRest->PromoteOrder(getoid(), getoexmoney());
}
int PromotionEvent::getoid()
{
	return OrderID;
}

double PromotionEvent::getoexmoney()
{
	return ExMony;
}


int PromotionEvent::getoarrivaltime()
{
	return OrdArrTime;
}

