#pragma once

#include <stdint.h>

enum class DigitNBits {
    A = 0x01,
    B = 0x02,
    C = 0x04,
    D = 0x08,
    E = 0x10,
    F = 0x20,
    G = 0x40
};

uint8_t operator&(DigitNBits digit, uint8_t mask) {
    uint8_t digitUint = (uint8_t)digit;
    return mask & digitUint;
}

uint8_t operator&(uint8_t mask, DigitNBits digit) {
    uint8_t digitUint = (uint8_t)digit;
    return mask & digitUint;
}

uint8_t operator|(DigitNBits digit, uint8_t mask) {
    uint8_t digitUint = (uint8_t)digit;
    return mask | digitUint;
}

uint8_t operator|(uint8_t mask, DigitNBits digit) {
    uint8_t digitUint = (uint8_t)digit;
    return mask | digitUint;
}