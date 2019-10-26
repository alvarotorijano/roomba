#pragma once

#include "State.hpp"

/**
 * Pushes an object.
 */
class PushState : public State {
public:
    /**
     * State constructor.
     * bot: Bot.
     */
    PushState(Bot *bot);

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