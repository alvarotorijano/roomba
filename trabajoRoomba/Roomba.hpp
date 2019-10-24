#pragma once

#include <SoftwareSerial.h>

#include "OpenInterface.hpp"

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define STRAIGHT 0x8000
#define CLOCKWISE 0xFFFF
#define COUNTER_CLOCKWISE 0x0001

/**
 * Roomba controller.
 */
class Roomba {
private:
    SoftwareSerial &serial;

public:
    Roomba(SoftwareSerial &_serial);

    void send(Opcode opcode, byte *operands, size_t length);
    void read(size_t length, void *output);

    void drive(int16_t velocity, int16_t radius);
    void driveStraight(int16_t velocity);
    void turnRight(int16_t velocity);
    void turnLeft(int16_t velocity);

    int16_t readAngle();
    int16_t readDistance();
    uint8_t readLightBumper();
    uint16_t readLightBumpLeftSignal();
    uint16_t readLightBumpFrontLeftSignal();
    uint16_t readLightBumpCenterLeftSignal();
    uint16_t readLightBumpCenterRightSignal();
    uint16_t readLightBumpFrontRightSignal();
    uint16_t readLightBumpRightSignal();
    void readLightBumpSignals(LightBumpSignals &output);
};