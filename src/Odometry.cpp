#include "Odometry.hpp"

#include <math.h>

#define FULL_TURN -27475.0
#define METER -29500.0

/**
 * Adds an odometry reading.
 */
void Odometry::add(int16_t _angle, int16_t _distance) {
    x += (_distance / METER) * cos(angle);
    y += (_distance / METER) * sin(angle);
    angle += _angle * 2 * M_PI / FULL_TURN;
    angle = fmod(angle, 2 * M_PI);
}

/**
 * Sets odometry to the specified position
 * angle: angle in radians.
 * x: x position in degrees.
 * y: y position in degrees.
 */
void Odometry::set(double _angle, double _x, double _y) {
    angle = _angle;
    x = _x;
    y = _y;
}