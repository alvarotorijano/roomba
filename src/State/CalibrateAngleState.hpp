#pragma once

#include "State.hpp"

/**
 * Finds an object.
 */
class CalibrateAngleState : public State {
private:
    int detections;
    int continuedDetections;
    bool finding;
    double time;
    unsigned long start;
public:
    /**
     * State constructor.
     * bot: Bot.
     */
    CalibrateAngleState(Bot *bot);

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