#include "Roomba.hpp"

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
void Roomba::send(Opcode opcode, byte *operands, size_t length) {
    serial.write((byte)opcode);
    serial.write(operands, length);
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
    byte operands[4];
    memcpy(operands, &velocity, 2);
    memcpy(operands + 2, &radius, 2);
    send(Opcode::DRIVE, operands, 4);
}

/**
 * Makes the Roomba drive at the specified velocity.
 * velocity: Velocity of the movement.
 */
void Roomba::driveStraight(int16_t velocity) {
    drive(velocity, STRAIGHT);
}

/**
 * Makes the Roomba turn right at the specified velocity.
 * velocity: Velocity of the movement.
 */
void Roomba::turnRight(int16_t velocity) {
    drive(velocity, CLOCKWISE);
}

/**
 * Makes the Roomba turn left at the specified velocity.
 * velocity: Velocity of the movement.
 */
void Roomba::turnLeft(int16_t velocity) {
    drive(velocity, COUNTER_CLOCKWISE);
}

/**
 * Stops the Roomba in place.
 */
void Roomba::stop() {
    drive(0, 0);
}