#pragma once

/**
 * Reply packet for a Sensor::GROUP_101 read.
 */
struct Group101Packet
{
    uint16_t encoderCountsLeft;
    uint16_t encoderCountsRight;
    uint8_t lightBumper;
    uint16_t lightBumpLeft;
    uint16_t lightBumpFrontLeft;
    uint16_t lightBumpCenterLeft;
    uint16_t lightBumpCenterRight;
    uint16_t lightBumpFrontRight;
    uint16_t lightBumpRight;
    uint8_t irOpcodeLeft;
    uint8_t irOpcodeRight;
    int16_t leftMotorCurrent;
    int16_t rightMotorCurrent;
    int16_t mainBrushCurrent;
    int16_t sideBrushCurrent;
    uint8_t stasis;
};