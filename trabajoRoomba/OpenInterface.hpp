#pragma once

/**
 * Roomba Open Interface Opcodes
 */
enum class Opcode {
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

/**
 * Roomba Open Interface Packets
 */
enum class Packet {
    BUMPS_AND_WHEEL_DROPS = 7,
    WALL = 8,
    CLIFF_LEFT = 9,
    CLIFF_FRONT_LEFT = 10,
    CLIFF_FRONT_RIGHT = 11,
    CLIFF_RIGHT = 12,
    VIRTUAL_WALL = 13,
    WHEEL_OVERCURRENTS = 14,
    DIRT_DETECT = 15,
    UNUSED_BYTE = 16,
    INFRARED_CHARACTER_OMNI = 17,
    INFRARED_CHARACTER_LEFT = 52,
    INFRARED_CHARACTER_RIGHT = 53,
    BUTTONS = 18,
    DISTANCE = 19,
    ANGLE = 20,
    CHARGING_STATE = 21,
    VOLTAGE = 22,
    CURRENT = 23,
    TEMPERATURE = 24,
    BATTERY_CHARGE = 25,
    BATTERY_CAPACITY = 26,
    WALL_SIGNAL = 27,
    CLIFF_LEFT_SIGNAL = 28,
    CLIFF_FRONT_LEFT_SIGNAL = 29,
    CLIFF_FRONT_RIGHT_SIGNAL = 30,
    CLIFF_RIGHT_SIGNAL = 31,
    UNUSED_1 = 32,
    UNUSED_2 = 33,
    CHARGING_SOURCES_AVAILABLE = 34,
    OI_MODE = 35,
    SONG_NUMBER = 36,
    SONG_PLAYING = 37,
    NUMBER_OF_STREAM_PACKETS = 38,
    REQUESTED_VELOCITY = 39,
    REQUESTED_RADIUS = 40,
    REQUESTED_RIGHT_VELOCITY = 41,
    REQUESTED_LEFT_VELOCITY = 42,
    RIGHT_ENCODER_COUNTS = 43,
    LEFT_ENCODER_COUNTS = 44,
    LIGHT_BUMPER = 45,
    LIGHT_BUMP_LEFT_SIGNAL = 46,
    LIGHT_BUMP_FRONT_LEFT_SIGNAL = 47,
    LIGHT_BUMP_CENTER_LEFT_SIGNAL = 48,
    LIGHT_BUMP_CENTER_RIGHT_SIGNAL = 49,
    LIGHT_BUMP_FRONT_RIGHT_SIGNAL = 50,
    LIGHT_BUMP_RIGHT_SIGNAL = 51,
    LEFT_MOTOR_CURRENT = 54,
    RIGHT_MOTOR_CURRENT = 55,
    MAIN_BRUSH_MOTOR_CURRENT = 56,
    SIDE_BRUSH_MOTOR_CURRENT = 57,
    STASIS = 58,
    LIGHT_BUMP_SIGNALS = 106
};

/**
 * Roomba Open Interface Charging States
 */
enum class ChargingState {
    NOT_CHARGING = 0,
    REACONDITIONING_CHARGING = 1,
    FULL_CHARGING = 2,
    TRICKLE_CHARGING = 3,
    WAITING = 4,
    CHARGING_FAULT_CONDITION = 5
};

enum class LightBumper {
    LEFT = 0x01,
    FRONT_LEFT = 0x02,
    CENTER_LEFT = 0x04,
    CENTER_RIGHT = 0x08,
    FRONT_RIGHT = 0x10,
    RIGHT = 0x20,
};

struct LightBumpSignals {
    uint16_t left;
    uint16_t frontLeft;
    uint16_t centerLeft;
    uint16_t centerRight;
    uint16_t frontRight;
    uint16_t right;
};

/**
 * Returns Roomba Opcodes operands length in bytes
 */
/*int getOperandsLength(Opcode opcode) {
    switch (opcode) {
        case Opcode::BAUD:
        case Opcode::MOTORS:
        case Opcode::BUTTONS:
        case Opcode::PLAY:
        case Opcode::SENSORS:
        case Opcode::RESUME_STREAM:
            return 1;
        case Opcode::SCHEDULING_LEDS:
            return 2;
        case Opcode::SET_TIME:
        case Opcode::PWM_MOTORS:
        case Opcode::LEDS:
            return 3;
        case Opcode::DRIVE:
        case Opcode::DRIVE_DIRECT:
        case Opcode::DRIVE_PWM:
        case Opcode::DIGIT_LEDS_RAW:
        case Opcode::DIGIT_LEDS_ASCII:
            return 4;
        case Opcode::SCHEDULE:
            return 15;
        case Opcode::SONG:
            return -1;
        case Opcode::QUERY_LIST:
        case Opcode::STREAM:
            return -2;
        case Opcode::START:
        case Opcode::SAFE:
        case Opcode::CONTROL:
        case Opcode::FULL:
        case Opcode::CLEAN:
        case Opcode::MAX:
        case Opcode::SPOT:
        case Opcode::SEEK_DOCK:
        case Opcode::POWER:
            return 0;
    }
}*/