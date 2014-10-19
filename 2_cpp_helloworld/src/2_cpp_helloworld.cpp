//============================================================================
// Name        : iotdk-cpp-template.cpp
// Author      : Intel Corporation
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "Service.h"
#include "Sensors.h"
#include "Actuators.h"
#include <string.h>
#include <time.h>

using namespace std;

namespace
{
	const unsigned int POLL_INTERVAL_USEC = 1000000;
	const unsigned int SAMPLE_INTERVAL = 10;
	const unsigned int DEFAULT_WATERING_TIME = 3;
}

int main() {
	Service s;
	s.informPlantWatered(1339);
	Sensors sensors(s);

	Actuators a(s);

	time_t readTime;
	time_t currentTime;
	time(&readTime);
	int overrideDurationFromApp;
	while(true)
	{
		bool switchState = sensors.readOverrideSwitch();
		printf("override switch : %i\n", switchState);
		if(switchState)
		{
			a.waterPlant(DEFAULT_WATERING_TIME);
		}
		overrideDurationFromApp = s.readServerData();
		if(overrideDurationFromApp != 0)
		{
			printf("Override from App received: Watering plant: %d\n", overrideDurationFromApp);
			a.waterPlant(overrideDurationFromApp);
			s.acknowledgeWater();
		}
		a.checkWateringStatus();
		time(&currentTime);
		if(difftime(currentTime, readTime) > SAMPLE_INTERVAL)
		{
			sensors.readSensorValues();
			time(&readTime);
		}

		printf("###\n");
		usleep(POLL_INTERVAL_USEC);
	}

	return 0;
}
