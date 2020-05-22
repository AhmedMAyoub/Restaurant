#include "CancellationEvent.h"



CancellationEvent::CancellationEvent() :Event(0, 0) //AM
{

}
CancellationEvent::CancellationEvent(int oTime, int oid) : Event(oTime, oid) //AM
{
	OrderID = oid;
}
void CancellationEvent::Execute(Restaurant* pRest)	 //A.M
{
	pRest->CancelOrder(OrderID);
}
int CancellationEvent::getoid()
{
	return OrderID;
}
