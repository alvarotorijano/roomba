#pragma once

#include "State.hpp"

/**
 * Dummy debug state.
 */
class DummyState : public State
{
public:
    /**
     * State constructor.
     * bot: Bot.
     */
    DummyState(Bot *bot);

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