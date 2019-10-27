#include "DummyState.hpp"

#include "../Bot.hpp"

#define FULL_TURN_READ -31283.20

/**
 * State constructor.
 * bot: Bot.
 */
DummyState::DummyState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void DummyState::enter() {
    double a = 0, b = 0;
    PositionSensors positionSensors;
    /*roomba.turnRight(64);
    roomba.turnRight(64);
    delay(13643);
    roomba.stop();
    roomba.getPositionSensors(&positionSensors);
    lcd.clear();
    lcd.print(positionSensors.angle * 360.0 / FULL_TURN_READ);*/
    /*for (int i = 0; i < 10; i++) {
        bot->roomba.turnRight(64);
        delay(13643);
        bot->roomba.stop();
        bot->roomba.getPositionSensors(&positionSensors);
        a += positionSensors.angle;
        delay(1000);
        bot->roomba.turnLeft(64);
        delay(13643);
        bot->roomba.stop();
        bot->roomba.getPositionSensors(&positionSensors);
        b += positionSensors.angle;
        delay(1000);
    }
    a /= 10;
    b /= 10;
    bot->lcd.clear();
    bot->lcd.print(a);
    bot->lcd.setCursor(0, 1);
    bot->lcd.print(b);*/
    /*bot->roomba.turnRight(64);
    delay(3411);
    bot->roomba.stop();
    bot->roomba.getPositionSensors(&positionSensors);
    bot->lcd.clear();
    bot->lcd.print((positionSensors.angle / FULL_TURN_READ) * 360.0);*/
    /*bot->roomba.driveStraight(64);
    delay(18188);
    bot->roomba.stop();
    bot->roomba.getPositionSensors(&positionSensors);
    bot->lcd.clear();
    bot->lcd.print(positionSensors.distance);*/
    bot->roomba.turnRight(64);
    delay(3410);
    bot->roomba.stop();
    bot->roomba.getPositionSensors(&positionSensors);
    bot->lcd.clear();
    bot->lcd.print(positionSensors.angle);
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void DummyState::update(unsigned long delta) {
    /*bot->lcd.clear();
    bot->lcd.print(bot->roomba.getWallSignal());
    delay(1000);*/
}

/**
 * Called when the state is exited.
 */
void DummyState::exit() {
}