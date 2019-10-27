#pragma once

#include "Bot.hpp"
#include "Leonidas.hpp"

#include "State/FaceState.hpp"
#include "State/SeekState.hpp"
#include "State/PushState.hpp"
#include "State/CalibrateAngleState.hpp"
#include "State/CalibrateDistanceState.hpp"
#include "State/MenuState.hpp"
#include "State/DummyState.hpp"
#include "State/SquareSideState.hpp"
#include "State/SquareCornerState.hpp"

#include <LiquidCrystal_I2C.h>

/**
 * Leonidas bot.
 */
class Leonidas : public Bot {
private:
    unsigned long lastRead;
public:
    /**
     * Searching state.
     */
    SeekState seek;

    /**
     * Facing state.
     */
    FaceState face;

    /**
     * Facing state.
     */
    PushState push;

    CalibrateAngleState calibrateAngle;

    MenuState menu;

    DummyState dummy;

    CalibrateDistanceState calibrateDistance;

    SquareSideState squareSide;

    SquareCornerState squareCorner;

    /**
     * Rotation angle.
     */
    double angle;

    /**
     * X coordinate.
     */
    double x;

    /**
     * Y coordinate.
     */
    double y;

    /**
     * Leonidas constructor.
     */
    Leonidas(SoftwareSerial &serial, LiquidCrystal_I2C &lcd);

    /**
     * Called on bot start.
     */
    void start();

    /**
     * Called periodically.
     * delta: Time delta.
     */
    void update(unsigned long delta);

    /**
     * Called on bot stop.
     */
    void stop();
};