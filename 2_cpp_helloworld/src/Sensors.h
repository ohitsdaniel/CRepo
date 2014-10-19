/*
 * Sensors.h
 *
 *  Created on: Oct 18, 2014
 *      Author: Lars
 */

#ifndef SENSORS_H_
#define SENSORS_H_

class Service;

namespace mraa
{
	class Aio;
	class Gpio;
}

class Sensors {
public:
	Sensors(const Service& service);
	virtual ~Sensors();

	void readSensorValues() const;

	double readHumidity() const;
	double readMoisture() const;
	double readTemperature() const;
	double readLight() const;
	bool readOverrideSwitch() const;

private:
	const Service& Servc;
	mraa::Aio* Temperature;
	mraa::Aio* Moisture;
	mraa::Aio* Humidity;
	mraa::Aio* Light;
	mraa::Gpio* Override;
};

#endif /* SENSORS_H_ */
