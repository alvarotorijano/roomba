#pragma once

#include "Roomba.hpp"
#include "State/State.hpp"
#include "State/IddleState.hpp"

#include <LiquidCrystal_I2C.h>

class State;

/**
 * Roomba bot.
 */
class Bot {
private:
    /**
     * State of the bot.
     */
    State &state;

public:
    /**
     * Iddle state.
     */
    IddleState iddle;

    /**
     * Roomba.
     */
    Roomba roomba;

    /**
     * LCD.
     */
    LiquidCrystal_I2C &lcd;

    /**
     * Bot constructor.
     */
    Bot(SoftwareSerial &serial, LiquidCrystal_I2C &_lcd);

    /**
     * Sets the state.
     * newState: Nuevo estado.
     */
    void setState(State &newState);

    /**
     * Gets the state.
     * returns the current state.
     */
    inline State &getState() {
        return state;
    }

    /**
     * Called on bot start.
     */
    virtual void start();

    /**
     * Called periodically.
     * delta: Time delta.
     */
    virtual void update(unsigned long delta);

    /**
     * Called on bot stop.
     */
    virtual void stop();
};