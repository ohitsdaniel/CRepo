/*
 * Service.h
 *
 *  Created on: Oct 18, 2014
 *      Author: Lars
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

class Service {
public:
	Service();
	virtual ~Service();

	void informPlantWatered(int duration) const;
	void sendSensorData(const std::string& sensorName, double value) const;
	void acknowledgeWater() const;
	int readServerData();

private:

	CURL *curl_handle;
	static int duration;

};

#endif /* SERVICE_H_ */
