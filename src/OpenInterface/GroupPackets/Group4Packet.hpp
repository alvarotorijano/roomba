#pragma once

#include <stdint.h>

/**
 * Reply packet for a Sensor::GROUP_4 read.
 */
struct Group4Packet
{
    uint16_t wallSignal;
    uint16_t cliffLeftSignal;
    uint16_t cliffFrontLeftSignal;
    uint16_t cliffFrontRightSignal;
    uint16_t cliffRightSignal;
    uint8_t unused2;
    uint16_t unused3;
    uint8_t chargerAvailable;
};

/**
 * Alias for Group4Packet.
 */
typedef Group4Packet CliffSignalSensors;