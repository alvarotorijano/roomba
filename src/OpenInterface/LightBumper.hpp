#pragma once

#include <stdint.h>

/**
 * Bit masks to extract light bumper information when reading
 * Sensor::LIGHT_BUMPER.
 */
enum class LightBumper
{
    LEFT = 0x01,
    FRONT_LEFT = 0x02,
    CENTER_LEFT = 0x04,
    CENTER_RIGHT = 0x08,
    FRONT_RIGHT = 0x10,
    RIGHT = 0x20,
};

bool operator&(LightBumper bumper, uint8_t mask) {
    uint8_t bumperUint = (uint8_t)bumper;
    return (mask & bumperUint) != 0;
}

bool operator&(uint8_t mask, LightBumper bumper) {
    uint8_t bumperUint = (uint8_t)bumper;
    return (mask & bumperUint) != 0;
}