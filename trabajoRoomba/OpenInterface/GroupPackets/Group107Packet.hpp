#pragma once

/**
 * Reply packet for a Sensor::GROUP_107 read.
 */
struct Group107Packet
{
    int16_t leftMotorCurrent;
    int16_t rightMotorCurrent;
    int16_t mainBrushCurrent;
    int16_t sideBrushCurrent;
    uint8_t stasis;
};

/**
 * Alias for Group107Packet.
 */
typedef Group107Packet CurrentSensors;