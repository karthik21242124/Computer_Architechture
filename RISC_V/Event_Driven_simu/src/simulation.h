/***********************************************************************
* FILENAME :        simulation.h
*
* DESCRIPTION :
*      declaration of class simulation
*      declaration of struct eventComp.
* MEMBERS :
*		protected MEQ - class memeber used as queue 
*		void scheduleEvent - to schedule events and push in the MEQ
*		void run - to run the simulations
* OTHER FUNCTIONS:
*		struct eventComp - returns value to sort the MEQ according to time. 
*		if the both left and right times are same, sorts according to value.
*
* AUTHOR :   Anuradha Patelkhana
*

**/
#pragma once
#include "event.h"
#include<queue>
#define MAXEVENT 100
struct eventComp {
	bool operator() ( Event* left,  Event* right) const {  
		if (left->getTime() == right->getTime()) /* if the time is same , sort according to value*/
			return(left->getVal() > right->getVal());
		return(left->getTime() > right->getTime());

	};

};
class Simulation {
public:
	Simulation() : MEQ() {}
	void scheduleEvent(Event* newE) {
		MEQ.push(newE);
	}
	void run(); 
protected:
	priority_queue < Event*, vector<Event*, allocator<Event*>>, eventComp >MEQ;
};
