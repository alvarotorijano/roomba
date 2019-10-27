#pragma once

#include "State.hpp"
#include <math.h>

/**
 * Finds an object.
 */
class GoBackState : public State  {
private:
	unsigned long start_time, duration;
    /**
     * Object detections.
     */
    int detections;
public:
    /**
     * State constructor.
     * bot: Bot.
     */
    GoBackState(Bot *bot);

    /**
     * Called when the state is entered.
     */
    void enter();

    /**
     * Called periodically.
     * delta: Time delta.
     */
    void update(unsigned long delta);

    /**
     * Called when the state is exited.
     */
    void exit();
};