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
void Roomba::drive(int16_t velocity, int16_t radius) {
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

/**
 * Reads the angle the roomba has turned.
 * returns the angle.
 */
int16_t Roomba::readAngle() {
    Packet packet = Packet::ANGLE;
    byte operands[1];
    memcpy(operands, &packet, 1);
    int16_t output;
    read(sizeof(output), &output);
    return output;
};

/**
 * Reads the distance the roomba has moved.
 * returns the distance.
 */
int16_t Roomba::readDistance() {
    Packet packet = Packet::DISTANCE;
    byte operands[1];
    memcpy(operands, &packet, 1);
    int16_t output;
    read(sizeof(output), &output);
    return output;
}

/**
 * Reads if light bumpers are triggered.
 * returns a bit map with the values (use enum LightBumper to access the
 * fields)
 */
uint8_t Roomba::readLightBumper() {
    Packet packet = Packet::LIGHT_BUMPER;
    byte operands[1];
    memcpy(operands, &packet, 1);
    uint8_t output;
    read(sizeof(output), &output);
    return output;
}

/**
 * Reads the left light bump signal.
 * returns the signal.
 */
uint16_t Roomba::readLightBumpLeftSignal() {
    Packet packet = Packet::LIGHT_BUMP_LEFT_SIGNAL;
    byte operands[1];
    memcpy(operands, &packet, 1);
    uint16_t output;
    read(sizeof(output), &output);
    return output;
}

/**
 * Reads the front left light bump signal.
 * returns the signal.
 */
uint16_t Roomba::readLightBumpFrontLeftSignal() {
    Packet packet = Packet::LIGHT_BUMP_FRONT_LEFT_SIGNAL;
    byte operands[1];
    memcpy(operands, &packet, 1);
    uint16_t output;
    read(sizeof(output), &output);
    return output;
}

/**
 * Reads the center left light bump signal.
 * returns the signal.
 */
uint16_t Roomba::readLightBumpCenterLeftSignal() {
    Packet packet = Packet::LIGHT_BUMP_CENTER_LEFT_SIGNAL;
    byte operands[1];
    memcpy(operands, &packet, 1);
    uint16_t output;
    read(sizeof(output), &output);
    return output;
}

/**
 * Reads the center right light bump signal.
 * returns the signal.
 */
uint16_t Roomba::readLightBumpCenterRightSignal() {
    Packet packet = Packet::LIGHT_BUMP_CENTER_RIGHT_SIGNAL;
    byte operands[1];
    memcpy(operands, &packet, 1);
    uint16_t output;
    read(sizeof(output), &output);
    return output;
}

/**
 * Reads the front right light bump signal.
 * returns the signal.
 */
uint16_t Roomba::readLightBumpFrontRightSignal() {
    Packet packet = Packet::LIGHT_BUMP_FRONT_RIGHT_SIGNAL;
    byte operands[1];
    memcpy(operands, &packet, 1);
    uint16_t output;
    read(sizeof(output), &output);
    return output;
}

/**
 * Reads the right light bump signal.
 * returns the signal.
 */
uint16_t Roomba::readLightBumpRightSignal() {
    Packet packet = Packet::LIGHT_BUMP_RIGHT_SIGNAL;
    byte operands[1];
    memcpy(operands, &packet, 1);
    uint16_t output;
    read(sizeof(output), &output);
    return output;
}

/**
 * Reads the light bump signals.
 * output: the signals.
 */
void Roomba::readLightBumpSignals(LightBumpSignals &output) {
    Packet packet = Packet::LIGHT_BUMP_SIGNALS;
    byte operands[1];
    memcpy(operands, &packet, 1);
    read(sizeof(output), &output);
}