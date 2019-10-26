#pragma once

#include <stdint.h>

/**
 * Reply packet for a Sensor::GROUP_106 read.
 */
struct Group106Packet
{
    uint16_t lightBumpLeft;
    uint16_t lightBumpFrontLeft;
    uint16_t lightBumpCenterLeft;
    uint16_t lightBumpCenterRight;
    uint16_t lightBumpFrontRight;
    uint16_t lightBumpRight;
};

/**
 * Alias for Group106Packet.
 */
typedef Group106Packet LightBumpSignalSensors;