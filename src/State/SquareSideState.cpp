#include "SquareSideState.hpp"

#include "../OpenInterface/DigitNBits.hpp"
#include "../Bot.hpp"
#include "../Leonidas.hpp"

/**
 * State constructor.
 * bot: Bot.
 */
SquareSideState::SquareSideState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void SquareSideState::enter() {
    uint8_t sideLeds[4] = {0x10, 0x50, 0x54, 0x5C};
    bot->lcd.setCursor(0, 0);
    bot->lcd.print("SQUARE SIDE");
    if (side == 0) {
        //bot->odometry.set(0, 0, 0);
    }
    bot->roomba.setDigitsRaw(sideLeds[side], 0, 0, 0);
    side++;
    side %= 4;
    bot->roomba.driveStraight(64);
    start = millis();
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void SquareSideState::update(unsigned long delta) {
    Leonidas *leo = (Leonidas *)bot;
    if (millis() - start >= 9094) {
        bot->setState(&leo->squareCorner);
    }
}

/**
 * Called when the state is exited.
 */
void SquareSideState::exit() {
    bot->roomba.stop();
}