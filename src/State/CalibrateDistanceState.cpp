#include "CalibrateAngleState.hpp"

#include "../Bot.hpp"
#include "../Leonidas.hpp"

#define DETECTION_THRESHOLD 5000
#define DETECTIONS 4
#define SPEED 512

/**
 * State constructor.
 * bot: Bot.
 */
CalibrateDistanceState::CalibrateDistanceState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void CalibrateDistanceState::enter() {
    finding = true;
    time = 0;
    bot->roomba.driveStraight(SPEED);
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void CalibrateDistanceState::update(unsigned long delta) {
    unsigned long now = millis();
    uint16_t wall = bot->roomba.getWallSignal();
    if (finding) {
        if (wall > DETECTION_THRESHOLD) {
            continuedDetections++;
        } else {
            continuedDetections = 0;
        }
    } else {
        if (wall <= DETECTION_THRESHOLD) {
            continuedDetections++;
        } else {
            continuedDetections = 0;
        }
    }
    if (continuedDetections >= DETECTIONS) {
        if (!finding) {
            if (start == 0) {
                start = millis();
            } else {
                bot->setState(&bot->iddle);
            }
        }
        continuedDetections = 0;
        finding = !finding;
    }
}

/**
 * Called when the state is exited.
 */
void CalibrateDistanceState::exit() {
    time = millis() - start;
    bot->roomba.stop();
    bot->lcd.clear();
    bot->lcd.setCursor(0, 0);
    bot->lcd.print(time);
}