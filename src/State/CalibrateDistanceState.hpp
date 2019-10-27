#pragma once

#include "State.hpp"

/**
 * Calibrates roomba distance
 */
class CalibrateDistanceState : public State {
private:
    int continuedDetections;
    bool finding;
    double time;
    unsigned long start;
public:
    /**
     * State constructor.
     * bot: Bot.
     */
    CalibrateDistanceState(Bot *bot);

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