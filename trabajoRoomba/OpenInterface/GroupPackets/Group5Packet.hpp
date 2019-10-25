#pragma once

/**
 * Reply packet for a Sensor::GROUP_5 read.
 */
struct Group5Packet
{
    uint8_t openInterfaceMode;
    uint8_t songNumber;
    uint8_t songPlaying;
    uint8_t oiStreamNumPackets;
    int16_t velocity;
    int16_t radius;
    int16_t velocityRight;
    int16_t velocityLeft;
};

/**
 * Alias for Group5Packet.
 */
typedef Group5Packet FeedbackSensors;