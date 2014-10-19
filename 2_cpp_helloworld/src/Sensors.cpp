/*
 * Sensors.cpp
 *
 *  Created on: Oct 18, 2014
 *      Author: Lars
 */

#include "Sensors.h"
#include "Service.h"
#include "mraa/aio.hpp"
#include "mraa/gpio.hpp"


namespace
{
	const unsigned int TEMPERATURE_PORT = 0;
	const unsigned int HUMIDITY_PORT = 2;
	const unsigned int WATER_PORT = 1;
	const unsigned int LIGHT_PORT = 3;

	const unsigned int OVERRIDE_PORT = 3;
}

Sensors::Sensors(const Service& service)
	: Servc(service)
	, Temperature(new mraa::Aio(TEMPERATURE_PORT))
	, Water(new mraa::Aio(WATER_PORT))
	, Humidity(new mraa::Aio(HUMIDITY_PORT))
	, Light(new mraa::Aio(LIGHT_PORT))
	, Override(new mraa::Gpio(OVERRIDE_PORT, true))
{
	Override->dir(mraa::DIR_IN);
}

Sensors::~Sensors() {
	// TODO Auto-generated destructor stub

	delete Override;
	Override = NULL;

	delete Light;
	Light = NULL;

	delete Humidity;
	Humidity = NULL;

	delete Water;
	Water = NULL;

	delete Temperature;
	Temperature = NULL;
}

void Sensors::readSensorValues()
{
	Servc.sendSensorData("Humidity", readHumidity());
	Servc.sendSensorData("Temperature", readTemperature());
	Servc.sendSensorData("Water", readWater());
	Servc.sendSensorData("Light", readLight());
}

double Sensors::readHumidity()
{
	humidity = Humidity->read();
	printf("Humidity: %.3f\n", humidity);
	return humidity;
}

double Sensors::readTemperature()
{
	temperature = Temperature->read() / 100.0;
	printf("Temperature: %.3f\n", temperature);
	return temperature;
}

double Sensors::readWater()
{
	water = Water->read() * 1.0;
	printf("Water: %.3f\n", water);
	return water;
}

double Sensors::readLight()
{
	light = Light->read() * 1.0;
	printf("Light: %.3f\n", light);
	return light;
}

bool Sensors::readOverrideSwitch() const
{
	return (Override->read() == 1 ? true : false);
}

