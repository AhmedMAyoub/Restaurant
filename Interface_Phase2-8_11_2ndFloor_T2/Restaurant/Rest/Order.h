#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money
	
	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	static int Promotiontime; // Time for normal order to get promoted automatically to vip order
	int EXMoney; // Money paid to upgrade normal order to vip order
	static int Tnormal; // Total number of normal orders
	static int Tvip; // Total number of vip orders
	static int Tvegan; // Total number of vegan order
	static int Wnormal; // Number of waiting normal orders
	static int Wvegan; // Number of waiting vegan orders
	static int Wvip; // Number of waiting vip orders
	static int VIP_WT;       // Max waiting time before VIP Order becomes urgent
	int Waitingtime;
	int Size;
	static int AutoPromoted; // Number of Auto-promoted normal orders
	static int wOrders;
	/////////////////////////////////////////////////Phase 2//////////////////////////////////////////////////
	static int Fnormal;      //Number Of Finished Normal Orders
	static int Fvip;         //Number Of Finished VIP    Orders
	static int Fvegan;       //Number Of Finished Vegan  Orders
	float Priority;
	static int Urgent;       //Number Of Urgent Orders

public:
	Order(int ID, ORD_TYPE r_Type);
	Order(int ID, ORD_TYPE r_Type, int arrivalTime, int size, double money);
	
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	void SetDistance(int d);
	int GetDistance() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	
	//
	// TODO: Add More Member Functions As Needed
	//
	
	void setOSize(int);
    void setWaitingTime(int);
	void setEXmoney(int);
	static void setPromotiontime(int);
	static void setAutoPromoted(int);
	static void setTnormal(int);
	static void setTvip(int);
	static void setTvegan(int);
	static void setWnormal(int);
	static void setWvip(int);
	static void setWvegan(int);
	static void setWOrders(int);
	void setServicetime(int);
	void setFinishedtime(int);
	void setArrivaltime(int);
	/////////////////////////////////////////////////Phase 2//////////////////////////////////////////////////
	static void setFnormal(int); 
	static void setFvip(int);    
	static void setFvegan(int);
     void setTotalMoney(int);
	 void SetType(ORD_TYPE);
	static void set_VIP_WT(int Maximum_waiting_time);
	void calculateVIPPriority(); //AM
	static void SetNumberofUrgent(int);
	
	


	int getOSize();
	int getWaitingTime();
	int getEXmoney();
	int getSevicetime();
	int getFinishedtime();
	int getArrivaltime();
	static int getPromotiontime();
	static int getAutoPromoted();
	static int getTnoraml();
	static int getTvip();
	static int getTvegan();
	static int getWnormal();
	static int getWvip();
	static int getWvegan();
	static int getWOrders();
	int get_VIP_WT();
	/////////////////////////////////////////////////Phase 2//////////////////////////////////////////////////
	static int getFnormal(); 
	static int getFvip();    
	static int getFvegan(); 
	 int getTotalMoney(); 
	 static int GetNumberOfUrgent();
	

	int Calcualte_Waiting_Time(int TimeStep, int ArrivalTime);
	bool GreaterThan_VIP_waitingTime(int waitingtime);
	float getPriority(); //AM
	void PrintArr(int, Order**);              //SF
	Order** SortSrvtime(int , Order** );      //SF
	Order** BubbleSortSrv(int, Order**);      //SF
	Order** Merge(int,Order**,int, Order**);  //SF
};

#endif
