#pragma once

#include <stdint.h>
#include <math.h>

/**
 * Odometry class.
 */
class Odometry {
private:
    double angle;
    double x;
    double y;
public:
    /**
     * Adds an odometry reading.
     * angle: angle of the reading.
     * distance: distance of the reading.
     */
    void add(int16_t angle, int16_t distance);

    /**
     * Sets odometry to the specified position
     * angle: angle in radians.
     * x: x position in degrees.
     * y: y position in degrees.
     */
    void set(double angle, double x, double y);

    /**
     * Gets the angle of the roomba, in radians.
     * returns the angle.
     */
    inline double getAngle() {
        return angle;
    }

    /**
     * Gets the angle of the roomba, in degrees.
     * returns the angle.
     */
    inline double getDegree() {
        return angle * 180.0 / M_PI;
    }

    /**
     * Gets the X position of the roomba, in meters.
     * returns the X position.
     */
    inline double getX() {
        return x;
    }

    /**
     * Gets the Y position of the roomba, in meters.
     * returns the Y position.
     */
    inline double getY() {
        return y;
    }
};