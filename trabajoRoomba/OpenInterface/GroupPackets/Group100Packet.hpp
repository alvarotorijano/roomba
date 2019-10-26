#pragma once

/**
 * Reply packet for a Sensor::GROUP_100 read.
 */
struct Group100Packet
{
    uint8_t bumpsWheeldrops;
    uint8_t wall;
    uint8_t cliffLeft;
    uint8_t cliffFrontLeft;
    uint8_t cliffFrontRight;
    uint8_t cliffRight;
    uint8_t virtualWall;
    uint8_t overcurrents;
    uint8_t dirtDetect;
    uint8_t unused1;
    uint8_t irOpcode;
    uint8_t buttons;
    int16_t distance;
    int16_t angle;
    uint8_t chargingState;
    uint16_t voltage;
    int16_t current;
    int8_t temperature;
    uint16_t batteryCharge;
    uint16_t batteryCapacity;
    uint16_t wallSignal;
    uint16_t cliffLeftSignal;
    uint16_t cliffFrontLeftSignal;
    uint16_t cliffFrontRightSignal;
    uint16_t cliffRightSignal;
    uint8_t unused2;
    uint16_t unused3;
    uint8_t chargerAvailable;
    uint8_t openInterfaceMode;
    uint8_t songNumber;
    uint8_t songPlaying;
    uint8_t oiStreamNumPackets;
    int16_t velocity;
    int16_t radius;
    int16_t velocityRight;
    int16_t velocityLeft;
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

/**
 * Alias for Group100Packet.
 */
typedef Group100Packet Sensors;