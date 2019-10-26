#pragma once

/**
 * Roomba Open Interface Opcodes
 */
enum class Opcode
{
    START = 128,
    BAUD = 129,
    CONTROL = 130,
    SAFE = 131,
    FULL = 132,
    POWER = 133,
    SPOT = 134,
    CLEAN = 135,
    MAX = 136,
    DRIVE = 137,
    MOTORS = 138,
    LEDS = 139,
    SONG = 140,
    PLAY = 141,
    SENSORS = 142,
    SEEK_DOCK = 143,
    PWM_MOTORS = 144,
    DRIVE_DIRECT = 145,
    DRIVE_PWM = 146,
    STREAM = 148,
    QUERY_LIST = 149,
    PAUSE_STREAM = 150,
    RESUME_STREAM = 150,
    SCHEDULING_LEDS = 162,
    DIGIT_LEDS_RAW = 163,
    DIGIT_LEDS_ASCII = 164,
    BUTTONS = 165,
    SCHEDULE = 167,
    SET_TIME = 168
};