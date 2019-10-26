#pragma once

#include <stdint.h>

/**
 * Reply packet for a Sensor::GROUP_0 read.
 */
struct Group0Packet
{
    uint8_t bumpsWheeldrops;
    uint8_t wall;
    uint8_t cliffLeft;
    uint8_t cliffFrontLeft;
    uint8_t cliffFrontRight;
    uint8_t cliffRight;
    uint8_t virtualWall;
    uint8_t overcurrents;
    uint8_t dirtDetect;
    uint8_t unused1;
    uint8_t irOpcode;
    uint8_t buttons;
    int16_t distance;
    int16_t angle;
    uint8_t chargingState;
    uint16_t voltage;
    int16_t current;
    int8_t temperature;
    uint16_t batteryCharge;
    uint16_t batteryCapacity;
};