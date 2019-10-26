#pragma once

#include "Bot.hpp"
#include "Leonidas.hpp"

#include "State/FaceState.hpp"
#include "State/SeekState.hpp"
#include "State/PushState.hpp"

#include <LiquidCrystal_I2C.h>

/**
 * Leonidas bot.
 */
class Leonidas : public Bot {
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