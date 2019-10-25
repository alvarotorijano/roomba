#ifndef SENSORPACK_T
#define SENSORPACK_T


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

typedef struct sensors {
	uint8_t bumpsWheelDrops;
	byte wall;
	byte cliffLeft;
	byte cliffFrontLeft;
	byte cliffFrontRight;
	byte cliffRight;
	byte virtualWall;
	byte overcurrents;
	byte dirtDetect;
	byte unused1;
	byte irOpcode;
	byte buttons;
	int16_t distance;	//Acumulative
	int16_t angle;		//Acumulative
	byte chargingState;
	int16_t voltage;
	int16_t current;
	int8_t temperature;
	uint16_t batteryCharge;
	uint16_t batteryCapacity;
	uint16_t wallSignal;
	uint16_t cliffLeftSignal;
	uint16_t cliffFrontLeftSignal;
	uint16_t cliffFrontRightSignal;
	uint16_t cliffRightSignal;
	byte unused2;
	int16_t unused3;
	byte chargerAvailable;
	byte openInterfaceMode;
	byte songNumber;
	byte songPlaying;
	byte OIStreamNumPackets;
	int16_t velocity;
	int16_t radius;
	int16_t velocityRight;
	int16_t velocityLeft;
	uint16_t encoderCountsLeft;  //Acumulative
	uint16_t encoderCountsRight; //Acumulative
	byte lightBumper;
	uint16_t lightBumpLeft;
	uint16_t lightBumpfrontLeft;
	uint16_t lightBumpCenterLeft;
	uint16_t lightBumpCenterRight;
	uint16_t lightBumpfrontRight;
	uint16_t lightBumpRight;
	byte irOPCodeLeft;
	byte irOPCodeRight;
	int16_t leftMotorCurrent;
	int16_t rightMotorCurrent;
	int16_t mainBrushCurrent;
	int16_t sideBrushCurrent;
	byte stasis;
} sensorPack_t;


#endif