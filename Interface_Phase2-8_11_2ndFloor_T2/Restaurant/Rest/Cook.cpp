#include "Cook.h"

int Cook::RstPrd = 0;
float Cook::InjProp = 0;
//initialization of static members

Cook::Cook()
{
}

Cook::~Cook()
{
}

int Cook::Generate_between_TwoNumbers(int LastNumber, int FirstNumber) {

	int RandomNumber = rand() % (LastNumber - (FirstNumber - 1)) + FirstNumber;

	return RandomNumber;
}

void Cook::setID(int id)
{
	ID = id;
}
int Cook::GetID() const
{
	return ID;
}


void Cook::setType(ORD_TYPE t)
{
	type = t;
}
ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setbreakorders(int bo)
{
	breakorders = bo;
}
int Cook::getbreakorders() const
{
	return breakorders;
}
///////////////////////////////////Phase 2 ////////////////////////////////
void Cook::SetMinSpeed(int MinS)
{
	MinSpeed = MinS;
}
int Cook::GetMinSpeed()
{
	return MinSpeed;
}


void Cook::SetMaxSpeed(int MaxS)
{
	MaxSpeed = MaxS;
}
int Cook ::GetMaxSpeed()
{
	return MaxSpeed;
}


void Cook::SetSpeed(int min, int max) {
	min = MinSpeed;
	max = MaxSpeed;
	Speed = Generate_between_TwoNumbers(max, min);
}

void Cook::SetXSpeed(int s) {
	Speed = Speed * s;
}

int Cook::GetSpeed() {
	return Speed;
}


void Cook::SetMinBreak(int MinB)
{
	MinBreak = MinB;
}
int Cook::GetMinBreak()
{
	return MinBreak;
}


void Cook::SetMaxBreak(int MaxB)
{
	MaxBreak = MaxB;
}
int Cook:: GetMaxBreak()
{
	return MaxBreak;
}


void Cook::SetBreak(int min, int max) {
	max = MaxBreak;
	min = MinBreak;
	Break = Generate_between_TwoNumbers(max, min);
}
int Cook::GetBreak(){
	return Break;
}

void Cook::SetBreakFinishTime(int prd, int ts) {
	breakFinishTime = prd + ts;
}
int Cook::GetBreakFinishTime() {
	return breakFinishTime;
}

void Cook::SetRstPrd(int val) {
	Cook::RstPrd = val;
}
int Cook::GetRstPrd() {
	return Cook::RstPrd;
}

void Cook::SetInjProp(float IP)
{
	Cook::InjProp = IP;
}
float Cook::GetInjProp()
{
	return Cook::InjProp;
}

void Cook::setordersdone(int i) {
	ordersDone = i;
}
int Cook::getordersdone() {
	return ordersDone;
}
void Cook::SetNumberOfInjured(int i)
{
	InjuredCooks = i;
}
int Cook::GetNumberOfInjured()
{
	return InjuredCooks;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void  Cook::setNumberofAvailableCooks( int A) {

	NumberOfAvailablecooks = A;
}

void Cook::setVIPAvailablecooks(int A) {

	VIPAvailablecooks = A;
}

void Cook::setNORMALAvailablecooks(int A) {

	NORAMALAvailablecooks = A;
}

void Cook::setVEGANAvailablecooks(int A) {

	VEGANAvailablecooks = A;
}

 void Cook::setNumberofCOOKS(int A) {

	NumberofCOOKS = A;
}


 void Cook::setFinishTime(int ft)
 {
	 finishTime = ft;
 }

 int Cook::getFinishTime()
 {
	 return finishTime;
 }


 void  Cook::setAssignedOrder(Order* order)
 {
	  AssignedOrder= order;
 }
 Order* Cook::getAssignedOrder()
 {
	 return AssignedOrder;
 }

 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Cook::getNumberofAvaialableCooks() {

	return NumberOfAvailablecooks;
}

int Cook::getVIPAvailablecooks() {

	return VIPAvailablecooks;
}

int Cook::getNORMALAvailablecooks() {

	return NORAMALAvailablecooks;
}

int Cook::getVEGANAvailablecooks() {

	return VEGANAvailablecooks;
}


int Cook::getNumberofCOOKS() {

	return NumberofCOOKS;
}



int Cook::NORAMALAvailablecooks = 0;
int Cook::NumberOfAvailablecooks = 0;
int Cook::VEGANAvailablecooks = 0;
int Cook::VIPAvailablecooks = 0; 
int Cook::InjuredCooks = 0;
