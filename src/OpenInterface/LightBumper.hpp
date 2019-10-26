#pragma once

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