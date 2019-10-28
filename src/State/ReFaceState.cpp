#include "ReFaceState.hpp"

#include "../Bot.hpp"
#include "../Leonidas.hpp"

/**
 * State constructor.
 * bot: Bot.
 */
ReFaceState::ReFaceState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void ReFaceState::enter() {
    bot->lcd.setCursor(0, 0);
	bot->lcd.print("Refacing");

    bot->roomba.turnRight(64);
    start = millis();
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void ReFaceState::update(unsigned long delta) {
    Leonidas *leo = (Leonidas *)bot;
    if (millis() - start >= 3400*2) {
        bot->setState(&leo->goBack);
    }
}

/**
 * Called when the state is exited.
 */
void ReFaceState::exit() {
    bot->roomba.stop();
}