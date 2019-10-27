#include "Roomba.hpp"

#include <math.h>

#define FULL_TURN_TIME 3033

/**
 * Roomba constructor.
 * _serial: SoftwareSerial object.
 */
Roomba::Roomba(SoftwareSerial &_serial)
    : serial(_serial)
{
}

/**
 * Sends an opcode and its operands to the Roomba.
 * opcode: Operation code.
 * operands: Array of operand bytes.
 * length: Length in bytes of the array of operands.
 */
void Roomba::send(Opcode opcode, uint8_t *operands, size_t length) {
    serial.write((uint8_t)opcode);
    if (operands != nullptr && length > 0) {
        serial.write(operands, length);
    }
}

/**
 * Reads output from the roomba.
 * length: Length of the data to read, in bytes.
 * output: Pointer to the memory to write.
 */
void Roomba::read(size_t length, void *output) {
    for (int i = 0; i < length; i++) {
        ((byte *)output)[i] = serial.read();
    }
}

/**
 * Makes the Roomba drive at the specified velocity with the specified radius.
 * velocity: Velocity of the movement.
 * radius: Radius of the movement.
 */
void Roomba::drive(int16_t velocity, int16_t radius)
{
    uint8_t operands[4];
    operands[0] = (0xFF00 & velocity) >> 8;
    operands[1] = 0x00FF & velocity;
    operands[2] = (0xFF00 & radius) >> 8;
    operands[3] = 0x00FF & radius;
    send(Opcode::DRIVE, operands, 4);
}

/**
 * Makes the Roomba turn.
 * angle: The angle to turn in radians.
 * velocity: The velocity of the turn.
 */
void Roomba::turn(float angle, int16_t velocity) {
    if (angle < 0) {
        angle = -angle;
        this->turnLeft(velocity);
    } else {
        this->turnRight(velocity);
    }
    delay((angle / (2.0 * PI)) * (FULL_TURN_TIME));
    stop();
}

/**
 * Makes the Roomba turn.
 * angle: The angle to turn in degrees.
 * velocity: The velocity of the turn.
 */
void Roomba::turnDegree(float angle, int16_t velocity) {
    if (angle < 0) {
        angle = -angle;
        this->turnLeft(velocity);
    } else {
        this->turnRight(velocity);
    }
    delay((angle / 360.0) * (FULL_TURN_TIME));
    stop();
}



/**
 * Sets the raw digit segment data.
 * digit1: Bits for first digit.
 * digit2: Bits for second digit.
 * digit3: Bits for third digit.
 * digit4: Bits for fourth digit.
 */
void Roomba::setDigitsRaw(uint8_t digit1, uint8_t digit2, uint8_t digit3,\
    uint8_t digit4)
{
    uint8_t operands[4];
    operands[0] = digit1;
    operands[1] = digit2;
    operands[2] = digit3;
    operands[3] = digit4;
    send(Opcode::DIGIT_LEDS_RAW, operands, 4);
}