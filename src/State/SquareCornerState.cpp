#include "SquareCornerState.hpp"

#include "../Bot.hpp"
#include "../Leonidas.hpp"

/**
 * State constructor.
 * bot: Bot.
 */
SquareCornerState::SquareCornerState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void SquareCornerState::enter() {
    bot->lcd.setCursor(0, 0);
    bot->lcd.print("SQUARE CORNER");
    bot->roomba.turnRight(64);
    start = millis();
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void SquareCornerState::update(unsigned long delta) {
    Leonidas *leo = (Leonidas *)bot;
    if (millis() - start >= 3410) {
        bot->setState(&leo->squareSide);
    }
}

/**
 * Called when the state is exited.
 */
void SquareCornerState::exit() {
    bot->roomba.stop();
}