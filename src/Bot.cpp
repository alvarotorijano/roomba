#include "Bot.hpp"

#include "State/IddleState.hpp"

Bot::Bot(SoftwareSerial &serial, LiquidCrystal_I2C &_lcd)
    : iddle(IddleState(this)), state(&iddle), roomba(Roomba(serial)), lcd(_lcd)
{
    state->enter();
}

void Bot::setState(State *newState) {
    state->exit();
    state = newState;
    state->enter();
}

/**
 * Called on bot start.
 */
void Bot::start() {}

/**
 * Called periodically.
 * delta: Time delta.
 */
void Bot::update(unsigned long delta) {
    state->update(delta);
}

/**
 * Called on bot stop.
 */
void Bot::stop() {}