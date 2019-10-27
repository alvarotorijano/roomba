#include "PushState.hpp"

#include "../Bot.hpp"
#include "../Leonidas.hpp"

/**
 * State constructor.
 * bot: Bot.
 */
PushState::PushState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void PushState::enter() {
    bot->lcd.clear();
    bot->lcd.setCursor(0, 0);
    bot->lcd.print("PUSH");
    bot->roomba.driveStraight(100);
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void PushState::update(unsigned long delta) {
    CliffSensors cliffs;
    bot->roomba.getCliffs(&cliffs);
    if (cliffs.cliffFrontLeft || cliffs.cliffFrontRight || cliffs.cliffLeft || cliffs.cliffRight) {
        bot->roomba.stop();
        Leonidas *leo = (Leonidas *)bot;
        bot->setState(&leo->reface);
    }
}

/**
 * Called when the state is exited.
 */
void PushState::exit() {
}