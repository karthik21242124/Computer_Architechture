/***********************************************************************
* FILENAME :        rand_eventSimu.cpp
*
* DESCRIPTION :
*      contains main()
* AUTHOR :   Anuradha Patelkhana
*
*
**/

#include <iostream>
#include <ctime>
#include "randevent.h"
using namespace std;

int main()
{
	cout << "Random Event Generator Simulation\n";
	time_t now = time(0);
	struct tm newTime;
	localtime_s(&newTime, &now);
	srand(0);
	randEvent_Generator EventGen((newTime.tm_sec), rand());
	cout << "Generating initial 20 events :" << endl;
	EventGen.initialize(20);
	//run the simulation
	EventGen.run();

	
}


