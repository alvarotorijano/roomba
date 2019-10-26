#include "FaceState.hpp"

#include "../Bot.hpp"
#include "../Leonidas.hpp"

/**
 * State constructor.
 * bot: Bot.
 */
FaceState::FaceState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void FaceState::enter() {
    bot->lcd.clear();
    bot->lcd.setCursor(0, 0);
    bot->lcd.print("FACE");
    bot->roomba.turnDegree(-35, 255);
    Leonidas *leo = (Leonidas *)bot;
    bot->setState(&leo->push);
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void FaceState::update(unsigned long delta) {

}

/**
 * Called when the state is exited.
 */
void FaceState::exit() {
}