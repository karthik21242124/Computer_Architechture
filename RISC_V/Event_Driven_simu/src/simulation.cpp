/***********************************************************************
* FILENAME :        simulation.cpp
*
* DESCRIPTION :
*      contains defination for run()
* AUTHOR :   Anuradha Patelkhana
*

**/


#include "simulation.h"
void Simulation::run() {
	int evCount = 0;
	while (evCount < MAXEVENT && !MEQ.empty()) { /* Empty is a library function of  queue*/
		cout << "Event Number: " << " " << evCount << endl;
		evCount++;
		Event* e = MEQ.top();
		MEQ.pop();
	//	cout << "running time: " << e->getTime() << "  " << "Value :"  << e->getVal() << endl;
		e->processEvent();
		delete e;
	}
}