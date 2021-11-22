/***********************************************************************
* FILENAME :        randevent.h
*
* DESCRIPTION :
*      declaration of child class eEvent
*      declaration of child class randEvent_Generator.
* MEMBERS :
*		1. randEvent_Generator
*		    rEvent *re - pointer to rEvent 
*			int evTime - time
*			int v - value
*			void genProcess - to generate events from 20 initial events
*			void initialize - to generate 20 events
*		2. class eEvent
*			randEvent_Generator *gen - pointer of randEvent_Generator
*			virtual voif process() - calls the genProcess function
*		void run - to run the simulations
* OTHER FUNCTIONS:
*		struct eventComp - returns value to sort the MEQ according to time.
*		if the both left and right times are same, sorts according to value.
*
* AUTHOR :   Anuradha Patelkhana
*

**/

#pragma once
#include "simulation.h"
class rEvent;
class randEvent_Generator : public Simulation {
private:
	//data fields
	rEvent* re;
	int evTime;
	int v;
public :
	
	randEvent_Generator() :Simulation(), evTime(0), v(0), re() {}
	randEvent_Generator( int etime,  int val) : Simulation(), evTime(etime), v(val), re(NULL){}
	void genProcess(int t, int v); // will be defined in cpp
	void initialize(int numEvent); // will be defined in cpp
	/*defining getters*/
	int getevTime() {
		return evTime;
	}
	int getv() {
		return v;
	}
	rEvent* getrEvent() {
		return re;
	}
	
};
class rEvent : public Event {
private :
	randEvent_Generator* gen; 
public:
	rEvent() :Event(), gen() {};
	rEvent(randEvent_Generator* g, int t, int val) :Event(t, val), gen(g) {}
	//override the virtual function
	virtual void processEvent() {
		//cout << " before calling genProcess" << " " << " time = " << getTime() << " value" << getVal() << endl;
		gen->genProcess(getTime(), getVal()); 
	} 

};