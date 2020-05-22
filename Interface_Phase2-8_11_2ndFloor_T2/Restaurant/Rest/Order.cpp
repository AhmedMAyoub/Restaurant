#include "Order.h"
#include "iostream"
using namespace std;

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
}

Order::Order(int id, ORD_TYPE r_Type, int arrivalTime, int size, double money)
{
	ID = (id>0 && id<1000) ? id : 0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	ArrTime = arrivalTime;
	totalMoney = money;
	Size = size;
	Priority = 0;
	calculateVIPPriority();
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

int Order::AutoPromoted = 0;
int Order::Promotiontime = 0;
int Order::Tnormal = 0;
int Order::Tvegan = 0;
int Order::Tvip = 0;
int Order::Wnormal = 0;
int Order::Wvegan = 0; 
int Order::Wvip = 0;
int Order::wOrders = 0;
/////////////////////////////////////////////////Phase 2//////////////////////////////////////////////////
int Order::Fnormal=0;
int Order::Fvip   =0;         
int Order::Fvegan =0;
int Order::VIP_WT = 0;
int Order::Urgent = 0;
void Order::setOSize(int s)
{
	Size = s;
}

void Order::setAutoPromoted(int A) {

	AutoPromoted = A;
}

void Order::setPromotiontime(int A) {

	Promotiontime = A;
}

void Order::setEXmoney(int A) {

	EXMoney = A;
}

void Order::setWaitingTime(int A) {

	Waitingtime = A;
}

void Order::setFinishedtime(int A) {

	FinishTime = A;
}

void Order::setServicetime(int A) {

	ServTime = A;
}

void Order::setArrivaltime(int AT)
{
	ArrTime = AT;
}

void Order::setTnormal(int A) {

	Tnormal = A;
}

void Order::setTvegan(int A) {

	Tvegan = A;
}

void Order::setTvip(int A) {

	Tvip = A;
}

void Order::setWnormal(int A) {

	Wnormal = A;
}

void Order::setWvegan(int A) {

	Wvegan = A;
}

void Order::setWvip(int A) {

	Wvip = A;
}

void Order::setWOrders(int A)
{
	wOrders = A;
}

void Order::set_VIP_WT(int Maximum_waitingtime) {

	VIP_WT = Maximum_waitingtime;
}


/////////////////////////////////////////////////Phase 2//////////////////////////////////////////////////
void Order::setFnormal(int FN)
{
	Fnormal = FN;
}


void Order::setFvip(int FVP)
{
	Fvip = FVP;
}


void Order::setFvegan(int FVG)
{
	Fvegan = FVG;
}

void Order::setTotalMoney(int TM)
{
	totalMoney = TM;
}

void Order::SetType(ORD_TYPE OT)
{
	type = OT;
}
void Order::calculateVIPPriority()
{
	if (type == VGAN_SPEED || type == TYPE_NRM)
	{
		return;
	}
	Priority = ((totalMoney*0.8) + (Size * 3)) / sqrt(ArrTime);
}

int Order::Calcualte_Waiting_Time(int TimeStep, int ArrivalTime) {

	int WaitingTime = TimeStep - ArrivalTime;

	return WaitingTime;

}

bool Order::GreaterThan_VIP_waitingTime(int waitingtime) {

	if (type != TYPE_VIP)
		return false;

	else {

		if (waitingtime > get_VIP_WT())

			return true;

		else

			return false;
	}
}

void Order::SetNumberofUrgent(int u)
{
	Urgent = u;
}


int Order::getSevicetime() {

	return ServTime;
}

int Order::getPromotiontime() {

	return Promotiontime;
}

int Order::getAutoPromoted() {

	return AutoPromoted;
}

int Order::getEXmoney() {

	return EXMoney;
}

int Order::getFinishedtime() {

	return FinishTime;
}

int Order::getWaitingTime() {

	return Waitingtime;
}

int Order::getArrivaltime()
{
	return ArrTime;
}

int Order::getTnoraml() {


	return Tnormal;
}

int Order::getTvegan() {

	return Tvegan;
}

int Order::getTvip() {

	return Tvip;
}

int Order::getWnormal() {

	return Wnormal;
}

int Order::getWvegan() {

	return Wvegan;
}

int Order::getWvip() {

	return Wvip;
}

int Order::getWOrders()
{
	return wOrders;
}
 

int Order::getOSize()
{
	return Size;
}
 
int Order::getFnormal()
{
	return Fnormal;
}
int Order::getFvip()
{
	return Fvip;
}
int Order::getFvegan()
{
	return Fvegan;
}

int Order::getTotalMoney()
{
	return totalMoney;
}


float Order::getPriority()
{
	return Priority;
}

int Order::get_VIP_WT() {

	return VIP_WT;
}

int Order::GetNumberOfUrgent()
{
	return Urgent;
}
/////////////////////////////////////////////////Phase 2//////////////////////////////////////////////////

void Order::PrintArr(int n, Order** op)            //SF
{
	cout << "print array"<<"  ";
	cout << n<<endl;
	for (int i = 0; i < n; i++)
	{
		Order *oop =op[i];
		cout << "index" << i << endl;
		cout << "ID" << oop->ID << endl;
		cout << "FinishTime" << oop->FinishTime << endl;
		cout << "inServTime" << oop->ServTime << endl;
	}
}
Order** Order::SortSrvtime(int count, Order** op)               //SF
{
	        //This Function  Assumes that the list is sorted by Finish time in Ascending Order
	
	Order** sorted = new Order * [count];     // Final Sorted Array in which  orders who  have the same FINISHED TIME are sorted by INSERVICE TIME
	bool flag = true;                         // A Flag to indicate if the Last Order was Added to the Final Sorted Array 
	int s = 0;    
	cout << "abl el 3k" << endl;
	PrintArr(count, op);//Index of Final FinishedOrders Array
	for (int i = 0; i < count-1; i++)
	{
		if (op[i] && op[i + 1] && op[i]->FinishTime < op[i + 1]->FinishTime)
		{
			cout << "op" << endl;
			cout << "Finished Time" << op[i]->getFinishedtime() << endl;
			cout << "Service Time" << op[i]->getFinishedtime() << endl;

			sorted[s] = op[i];
			cout << "s" << s << endl;
			cout << "Finished Time" << sorted[s]->getFinishedtime() << endl;
			cout << "Service Time" << sorted[s]->getFinishedtime() << endl;
			PrintArr(s+1, sorted);
			s++;
			int number = i;
			if (number=count-2)                    //If the Order before the last had a FINISHTIME less than the last Order
			{
				flag = false;                      // Last order wont be inserted in the Final Sorted Array
			} 
			
		}
		else if (op[i] && op[i + 1] && op[i]->FinishTime == op[i + 1]->FinishTime)
		{
			
			int FT = op[i]->FinishTime;
			int j = 0;
			j++;
			while (op[i + j]->FinishTime == FT)
			{
				j++;                                          //Count Number of Orders Who have the Same FINISHED TIME
			}
			
			Order** unsorted = new Order * [j];                //Temp Array to store orders who have the same FINISH TIME 
			int m = 0;                                         //Index of unsorted Array  
			for (int k = i; k < i + j; k++)
			{
				unsorted[m] = op[k];
				m++;

			}

			Order** Sortedbysrv = BubbleSortSrv(j, unsorted); //Sort the Orders who have the same FINISHTIME  by INSERVICE TIME
			cout << "bubble Sort" << endl;
			PrintArr(j,Sortedbysrv);
			
			sorted = Merge(s, sorted, j, Sortedbysrv);        //Merge the Final Sorted Array with the Array sorted by INSERVICE TIME 
			cout << "Merge" << endl;
			
			s = s + j;
			i = i + j - 1;

			PrintArr(s, sorted);


		}
	}

	if (!flag)                                           // If Last Order was not iserted in Finishedorders Array

	{
		Order** lastelement = new Order * [1];
		lastelement[0] = op[count - 1];
		sorted = Merge(s, sorted, 1, lastelement);       // Merge the Last Order with the Final Sorted Array
		cout << "flag";
		PrintArr(s, sorted);

		return sorted;
	}
	
	else return sorted;

}

Order** Order :: BubbleSortSrv(int count, Order** op)                                   //SF
{
	bool swaped;
	do
	{
		swaped = false;
		for (int k = 0; k < count-1; k++)
		{
			if (op[k]&&op[k+1]&&op[k]->getSevicetime() > op[k + 1]->getSevicetime())
			{
				Order* temp = op[k];
				op[k] = op[k + 1];
				op[k + 1] = temp;
				swaped = true;
			}
		}
	} while (swaped);
	return op;
}

Order ** Order::Merge(int size1,Order** sorted,int size2, Order** unsorted)       //SF
{
	int i, k;
	Order** merge=new Order*[size1+size2];
	for ( i = 0; i < size1; i++)
	{
		merge[i] = sorted[i];
	}
	for ( i=0,k = size1; k < size1 + size2 && i<size2 ;i++, k++)
	{
		merge[k] = unsorted[i];
	}

	return merge;
}
