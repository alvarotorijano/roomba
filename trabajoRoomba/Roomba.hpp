#pragma once

#include <SoftwareSerial.h>

#include "OpenInterface/Opcode.hpp"
#include "OpenInterface/Sensor.hpp"
#include "OpenInterface/GroupPackets/LightBumpSignalSensors.hpp"
#include "OpenInterface/GroupPackets/CliffSensors.hpp"

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
     * Sends an opcode without operands to the Roomba.
     * opcode: Operation code.
     */
    inline void send(Opcode opcode) {
        send(opcode, nullptr, 0);
    }

    /**
     * Reads output from the roomba.
     * length: Length of the data to read, in bytes.
     * output: Pointer to the memory to write.
     */
    void read(size_t length, void *output);



    /**
     * Reads the value of a sensor.
     * sensor: Sensor to query.
     */
    template <class T>
    T querySensor(Sensor sensor) {
        T output;
        querySensor<T>(sensor, &output);
        return output;
    }

    /**
     * Reads the value of a sensor.
     * sensor: Sensor to query.
     * output: Output reference.
     */
    template <class T>
    void querySensor(Sensor sensor, T &output)
    {
        byte operand = (byte)sensor;
        send(Opcode::SENSORS, &operand, 1);
        read(sizeof(T), &output);
    }

    /**
     * Reads the value of a sensor.
     * sensor: Sensor to query.
     * output: Output pointer.
     */
    template <class T>
    void querySensor(Sensor sensor, T *output) {
        byte operand = (byte)sensor;
        send(Opcode::SENSORS, &operand, 1);
        read(sizeof(T), output);
    }



    /**
     * Boots the Roomba.
     */
    inline void start()
    {
        send(Opcode::START);
    }

    /**
     * Sets Roomba mode to safe.
     */
    inline void setSafeMode()
    {
        send(Opcode::SAFE);
    }

    /**
     * Sets Roomba mode to full.
     */
    inline void setFullMode()
    {
        send(Opcode::FULL);
    }



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
    inline void driveStraight(int16_t velocity)
    {
        drive(velocity, STRAIGHT);
    }

    /**
     * Makes the Roomba turn right at the specified velocity.
     * velocity: Velocity of the movement.
     */
    inline void turnRight(int16_t velocity)
    {
        drive(velocity, CLOCKWISE);
    }

    /**
     * Makes the Roomba turn left at the specified velocity.
     * velocity: Velocity of the movement.
     */
    inline void turnLeft(int16_t velocity)
    {
        drive(velocity, COUNTER_CLOCKWISE);
    }

    /**
     * Makes the Roomba turn.
     * angle: The angle to turn in radians.
     * velocity: The velocity of the turn.
     */
    void turn(float angle, int16_t velocity);

    /**
     * Makes the Roomba turn.
     * angle: The angle to turn in degrees.
     * velocity: The velocity of the turn.
     */
    void turnDegree(float angle, int16_t velocity);

    /**
     * Stops the Roomba in place.
     */
    inline void stop()
    {
        drive(0, 0);
    }

    /**
     * Reads the angle the roomba has turned.
     * returns the angle.
     */
    inline int16_t getAngle() {
        return querySensor<int16_t>(Sensor::ANGLE);
    }

    /**
     * Reads the distance the roomba has moved.
     * returns the distance.
     */
    inline int16_t getDistance() {
        return querySensor<int16_t>(Sensor::DISTANCE);
    }



    /**
     * Reads if light bumpers are triggered.
     * returns a bit map with the values (use enum LightBumper to access the
     * fields)
     */
    inline uint8_t getLightBumper() {
        return querySensor<uint8_t>(Sensor::LIGHT_BUMPER);
    }

    /**
     * Reads the left light bump signal.
     * returns the signal.
     */
    inline uint16_t getLightBumpLeftSignal() {
        return querySensor<uint16_t>(Sensor::LIGHT_BUMP_LEFT_SIGNAL);
    }

    /**
     * Reads the front left light bump signal.
     * returns the signal.
     */
    inline uint16_t getLightBumpFrontLeftSignal() {
        return querySensor<uint16_t>(Sensor::LIGHT_BUMP_FRONT_LEFT_SIGNAL);
    }

    /**
     * Reads the center left light bump signal.
     * returns the signal.
     */
    inline uint16_t getLightBumpCenterLeftSignal() {
        return querySensor<uint16_t>(Sensor::LIGHT_BUMP_CENTER_LEFT_SIGNAL);
    }

    /**
     * Reads the center right light bump signal.
     * returns the signal.
     */
    inline uint16_t getLightBumpCenterRightSignal() {
        return querySensor<uint16_t>(Sensor::LIGHT_BUMP_CENTER_RIGHT_SIGNAL);
    }

    /**
     * Reads the front right light bump signal.
     * returns the signal.
     */
    inline uint16_t getLightBumpFrontRightSignal() {
        return querySensor<uint16_t>(Sensor::LIGHT_BUMP_FRONT_RIGHT_SIGNAL);
    }

    /**
     * Reads the right light bump signal.
     * returns the signal.
     */
    inline uint16_t getLightBumpRightSignal() {
        return querySensor<uint16_t>(Sensor::LIGHT_BUMP_RIGHT_SIGNAL);
    }

    /**
     * Reads the light bump signals.
     * output: the signals.
     */
    inline void getLightBumpSignals(LightBumpSignalSensors &output) {
        querySensor<LightBumpSignalSensors>(Sensor::LIGHT_BUMP_SIGNALS);
    }



    /**
     * Is left cliff sensor triggered?
     * returns 0 if it is, 1 if it isn't.
     */
    inline uint8_t getCliffLeft() {
        return querySensor<uint8_t>(Sensor::CLIFF_LEFT);
    }

    /**
     * Is front left cliff sensor triggered?
     * returns 0 if it is, 1 if it isn't.
     */
    inline uint8_t getCliffFrontLeft() {
        return querySensor<uint8_t>(Sensor::CLIFF_FRONT_LEFT);
    }

    /**
     * Is front right cliff sensor triggered?
     * returns 0 if it is, 1 if it isn't.
     */
    inline uint8_t getCliffFrontRight() {
        return querySensor<uint8_t>(Sensor::CLIFF_FRONT_RIGHT);
    }

    /**
     * Is right cliff sensor triggered?
     * returns 0 if it is, 1 if it isn't.
     */
    inline uint8_t getCliffRight() {
        return querySensor<uint8_t>(Sensor::CLIFF_RIGHT);
    }

    /**
     * Reads all cliff sensors.
     * output: the sensor values.
     */
    inline void getCliffs(CliffSensors &output) {
        querySensor<CliffSensors>(Sensor::CLIFFS, output);
    }

};
