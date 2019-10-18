#pragma once
#ifndef ROOMBALIB_H
#define ROOMBALIB_H

#include "SoftwareSerial.h"

typedef struct {

}sensor_t;

class roomba {
private:
	sensor_t sensor;
	SoftwareSerial* roombaPort;

public:
	roomba(byte tx, byte rx);

	void rommbaInit(void);

	void turn(int degre);

	void goForward(int mm);

	void readSensors(sensor_t roombaSensors);

};



#endif //ROOMBALIB_H
