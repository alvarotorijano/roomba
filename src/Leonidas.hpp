#pragma once

#include "Bot.hpp"
#include "Leonidas.hpp"

#include "State/SeekState.hpp"

#include <LiquidCrystal_I2C.h>

/**
 * Leonidas bot.
 */
class Leonidas : public Bot {
public:
    SeekState seek;

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