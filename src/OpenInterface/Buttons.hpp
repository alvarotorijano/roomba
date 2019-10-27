#pragma once

enum class Buttons {
    CLEAN = 0x01,
    SPOT = 0x02,
    DOCK = 0x04,
    MINUTE = 0x08,
    HOUR = 0x10,
    DAY = 0x20,
    SCHEDULE = 0x40,
    CLOCK = 0x80
};

bool operator&(Buttons button, uint8_t mask) {
    uint8_t buttonUint = (uint8_t)button;
    return (mask & buttonUint) != 0;
}

bool operator&(uint8_t mask, Buttons button) {
    uint8_t buttonUint = (uint8_t)button;
    return (mask & buttonUint) != 0;
}