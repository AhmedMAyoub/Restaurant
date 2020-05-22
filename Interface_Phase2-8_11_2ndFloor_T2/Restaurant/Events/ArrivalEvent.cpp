#include "ArrivalEvent.h"




ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType) :Event(eTime, oID)
{
	OrdType = oType;
}
void ArrivalEvent::Execute(Restaurant* pRest) //AM
{
	pRest->ArrivalOfOrder(getoid(), getotype(), getoarrivaltime(), getosize(), getomoney());
}
int ArrivalEvent::getoid()
{
	return OrderID;
}
double ArrivalEvent::getomoney()
{
	return OrdMony;
}
ArrivalEvent::ArrivalEvent() :Event(0, 0)
{

}
ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int OSize, double OMony):Event(eTime ,oID)
{
	OrdType = oType;
	OrdSize = OSize;
	OrdMony = OMony;
	OrdID = oID;
	OrdArrTime = eTime;
}

int ArrivalEvent::getosize()
{
	return OrdSize;
}

ORD_TYPE ArrivalEvent::getotype()
{
	return OrdType;
}
int ArrivalEvent::getoarrivaltime()
{
	return OrdArrTime;
}