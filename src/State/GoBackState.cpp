#include "GoBackState.hpp"

#include "../Bot.hpp"
#include "../Leonidas.hpp"

#define DETECTION_THRESHOLD 12000
#define DETECTIONS 3

/**
 * State constructor.
 * bot: Bot.
 */
GoBackState::GoBackState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void GoBackState::enter() {

	double distance; 

    bot->lcd.clear();
    bot->lcd.setCursor(0, 0);
    bot->lcd.print("SEEK");

	PositionSensors positionSensors;
	bot->roomba.getPositionSensors(&positionSensors);
	bot->odometry.add(positionSensors.angle, positionSensors.distance);

	distance = sqrt((bot->odometry.getX() * bot->odometry.getX()) + (bot->odometry.getY() * bot->odometry.getY()));

	duration = distance / 18188;

	this->start_time = millis();
    bot->roomba.driveStraight(64);

}

/**
 * Called periodically.
 * delta: Time delta.
 */
void GoBackState::update(unsigned long delta) {
	Leonidas* leo = (Leonidas*)bot;
	if (millis() - start_time >= duration) {
		bot->setState(&leo->iddle);
	}
}

/**
 * Called when the state is exited.
 */
void GoBackState::exit() {
	bot->roomba.stop();
}