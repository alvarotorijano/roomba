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
    /**
     * Roomba constructor.
     * _serial: SoftwareSerial object.
     */
    Roomba(SoftwareSerial &_serial);



    /**
     * Sends an opcode and its operands to the Roomba.
     * opcode: Operation code.
     * operands: Array of operand bytes.
     * length: Length in bytes of the array of operands.
     */
    void send(Opcode opcode, byte *operands, size_t length);

    /**
     * Reads output from the roomba.
     * length: Length of the data to read, in bytes.
     * output: Pointer to the memory to write.
     */
    void read(size_t length, void *output);



    /**
     * Makes the Roomba drive at the specified velocity with the specified radius.
     * velocity: Velocity of the movement.
     * radius: Radius of the movement.
     */
    void drive(int16_t velocity, int16_t radius);

    /**
     * Makes the Roomba drive at the specified velocity.
     * velocity: Velocity of the movement.
     */
    void driveStraight(int16_t velocity);

    /**
     * Makes the Roomba turn right at the specified velocity.
     * velocity: Velocity of the movement.
     */
    void turnRight(int16_t velocity);

    /**
     * Makes the Roomba turn left at the specified velocity.
     * velocity: Velocity of the movement.
     */
    void turnLeft(int16_t velocity);

    /**
     * Stops the Roomba in place.
     */
    void stop();



    /**
     * Reads the angle the roomba has turned.
     * returns the angle.
     */
    int16_t readAngle();

    /**
     * Reads the distance the roomba has moved.
     * returns the distance.
     */
    int16_t readDistance();



    /**
     * Reads if light bumpers are triggered.
     * returns a bit map with the values (use enum LightBumper to access the
     * fields)
     */
    uint8_t readLightBumper();

    /**
     * Reads the left light bump signal.
     * returns the signal.
     */
    uint16_t readLightBumpLeftSignal();

    /**
     * Reads the front left light bump signal.
     * returns the signal.
     */
    uint16_t readLightBumpFrontLeftSignal();

    /**
     * Reads the center left light bump signal.
     * returns the signal.
     */
    uint16_t readLightBumpCenterLeftSignal();

    /**
     * Reads the center right light bump signal.
     * returns the signal.
     */
    uint16_t readLightBumpCenterRightSignal();

    /**
     * Reads the front right light bump signal.
     * returns the signal.
     */
    uint16_t readLightBumpFrontRightSignal();

    /**
     * Reads the right light bump signal.
     * returns the signal.
     */
    uint16_t readLightBumpRightSignal();

    /**
     * Reads the light bump signals.
     * output: the signals.
     */
    void readLightBumpSignals(LightBumpSignals &output);
};