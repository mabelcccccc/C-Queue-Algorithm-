#ifndef STUDENT_H
#define STUDENT_H

#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

class Student
{

public:
    int name;
    int arrivalTime;
    int primaryServerTime;
    int secondaryServerTime;
    int arrivalSecondaryQTime;


    Customer(int name,int arrivalTime,int primaryServerTime,int secondaryServerTime);
    ~Customer() { } 

   int getName();
   int getarrivalTime();
   int getarrivalSecondaryQTime();
   void setarrivalSecondaryQTime(int);
   int getprimaryServerTime();
   void decrementPrimaryServerTime();
   void decrementSecondaryServerTime();
   int getsecondaryServerTime();
   string toString();

};

#endif //  STUDENT_H