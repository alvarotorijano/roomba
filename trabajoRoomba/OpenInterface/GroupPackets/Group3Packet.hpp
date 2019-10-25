#pragma once

/**
 * Reply packet for a Sensor::GROUP_3 read.
 */
struct Group3Packet
{
    uint8_t chargingState;
    uint16_t voltage;
    int16_t current;
    int8_t temperature;
    uint16_t batteryCharge;
    uint16_t batteryCapacity;
};

/**
 * Alias for Group3Packet.
 */
typedef Group3Packet BatterySensors;