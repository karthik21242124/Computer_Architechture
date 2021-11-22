/***********************************************************************
* FILENAME :        randevent.cpp
*
* DESCRIPTION :
*      contains definations for void genProcess(int t, int v)
*	   contains defination for void initialize(int n)
* AUTHOR :   Anuradha Patelkhana
*

**/

#include"randevent.h"
void
randEvent_Generator::genProcess(int t, int v) {
	cout << "Event time: " << t << " " << " Value : " << v << endl;
	t += (rand() % v) +1;
	v = rand() % 80 + 1;
	//now we have to schedule a new event , it is in simulation
	Event* EV = new rEvent(this, t, v);
	scheduleEvent(EV);
	//scheduleEvent(new rEvent(this, t, v));

}
void randEvent_Generator::initialize(int n) {
	/* 20 events will be generated first from here*/
	for (int i = 0; i < n; i++)
	{
		cout << "Initial time: " << getevTime() << " " << " Value : " << getv() << endl;
		int tt = evTime;
		scheduleEvent(new rEvent(this, evTime, v));
		evTime += (rand() % v) + 1;
		v = rand() % 20 + 1;
	}

}