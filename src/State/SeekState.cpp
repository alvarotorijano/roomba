#include "SeekState.hpp"

#include "../Bot.hpp"

#define DETECTION_THRESHOLD 12000
#define DETECTIONS 3

/**
 * State constructor.
 * bot: Bot.
 */
SeekState::SeekState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void SeekState::enter() {
    bot->lcd.setCursor(0, 0);
    bot->lcd.print("SEEK");
    bot->roomba.turnRight(5);
    detections = 0;
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void SeekState::update(unsigned long delta) {
    if (bot->roomba.getLightBumpLeftSignal() > DETECTION_THRESHOLD) {
        detections++;
    }
    if (detections >= DETECTIONS) {
        bot->lcd.setCursor(0, 0);
        bot->lcd.print("FOUND");
        bot->setState(bot->iddle);
    }
}

/**
 * Called when the state is exited.
 */
void SeekState::exit() {
}