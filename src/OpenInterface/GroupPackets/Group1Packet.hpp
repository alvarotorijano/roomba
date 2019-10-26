#pragma once

#include <stdint.h>

/**
 * Reply packet for a Sensor::GROUP_1 read.
 */
struct Group1Packet
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
};

/**
 * Alias for Group1Packet.
 */
typedef Group1Packet CliffSensors;