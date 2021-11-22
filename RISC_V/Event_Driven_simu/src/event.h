/***********************************************************************
* FILENAME :        event.h             
*
* DESCRIPTION :
*      Event abstract class.
* PARAMETERS :
*       This class is a base class which has two parameters 
*		int t for time
*		int v for value
* AUTHOR :   Anuradha Patelkhana       
*

**/



#pragma once
#include <iostream>
using namespace std;
class Event {
private:
	int val;
	int t;
public:
	Event() :t(0), val(0) {}
	Event(int et, int eval) :t(et), val(eval) {}
	virtual void processEvent()= 0; // = 0 is a pure vitual method
	int getVal()
	{
		return val;
	}
	int getTime()
	{
		return t;
	}

 };
