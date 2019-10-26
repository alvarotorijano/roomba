#pragma once

#include "State.hpp"

/**
 * Finds and object.
 */
class SeekState : public State
{
private:
    /**
     * Object detections.
     */
    int detections;
public:
    /**
     * State constructor.
     * bot: Bot.
     */
    SeekState(Bot *bot);

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