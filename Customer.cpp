#include "Customer.h"

int name;
int arrivalTime;
int primaryServerTime;
int secondaryServerTime;
int arrivalSecondaryQTime;

Customer::Customer(int name,int arrivalTime,int primaryServerTime,int secondaryServerTime):
    name(name), arrivalTime(arrivalTime), primaryServerTime(primaryServerTime), secondaryServerTime(secondaryServerTime){
    }

int Customer::getName()
{
    return this->name;
}

int Customer::getarrivalTime()
{
    return this->arrivalTime;
}

int Customer::getarrivalSecondaryQTime()
{
    return this->arrivalTime;
}

void Customer::setarrivalSecondaryQTime(int arrivalSecondaryQTime)
{
     this->arrivalSecondaryQTime = arrivalSecondaryQTime;
}

int Customer::getprimaryServerTime()
{
    return this->primaryServerTime;
}

void Customer::decrementPrimaryServerTime()
{
    this->primaryServerTime --;
}

int Customer::getsecondaryServerTime()
{
    return this->secondaryServerTime;
}

void Customer::decrementSecondaryServerTime()
{
    this->secondaryServerTime --;
}

string Customer::toString()
{   
    string s= "Customer [" + to_string(name) + "]" + " arrivalTime:"+ to_string(arrivalTime) + " primaryServerTime:"+  to_string(primaryServerTime) + "  secondaryServerTime:" + to_string(secondaryServerTime); 
    return s;
}







