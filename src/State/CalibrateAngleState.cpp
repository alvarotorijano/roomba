#include "CalibrateAngleState.hpp"

#include "../Bot.hpp"
#include "../Leonidas.hpp"

#define DETECTION_THRESHOLD 12000
#define DETECTIONS 4
#define REPETITIONS 10
#define SPEED 64

/**
 * State constructor.
 * bot: Bot.
 */
CalibrateAngleState::CalibrateAngleState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void CalibrateAngleState::enter() {
    detections = 0;
    finding = true;
    time = 0;
    bot->roomba.turnRight(SPEED);
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void CalibrateAngleState::update(unsigned long delta) {
    unsigned long now = millis();
    uint16_t bump = bot->roomba.getLightBumpLeftSignal();
    if (finding) {
        if (bump > DETECTION_THRESHOLD) {
            continuedDetections++;
        } else {
            continuedDetections = 0;
        }
    } else {
        if (bump <= DETECTION_THRESHOLD) {
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
                detections++;
                bot->lcd.clear();
                bot->lcd.print(detections);
            }
        }
        continuedDetections = 0;
        finding = !finding;
    }
    if (detections >= REPETITIONS) {
        bot->setState(&bot->iddle);
    }
}

/**
 * Called when the state is exited.
 */
void CalibrateAngleState::exit() {
    time = millis() - start;
    bot->roomba.stop();
    bot->lcd.clear();
    bot->lcd.setCursor(0, 0);
    bot->lcd.print(time / REPETITIONS);
}