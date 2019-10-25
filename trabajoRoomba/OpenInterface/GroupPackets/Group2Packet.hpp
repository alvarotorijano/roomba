#pragma once

/**
 * Reply packet for a Sensor::GROUP_2 read.
 */
struct Group2Packet
{
    uint8_t irOpcode;
    uint8_t buttons;
    int16_t distance;
    int16_t angle;
};

/**
 * Alias for Group2Packet.
 */
typedef Group2Packet PositionSensors;